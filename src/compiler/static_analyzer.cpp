/*
** GB BASIC
**
** Copyright (C) 2023-2025 Tony Wang, all rights reserved
**
** For the latest info, see https://paladin-t.github.io/kits/gbb/
*/

#include "kernel.h"
#include "static_analyzer.h"
#include "../utils/datetime.h"
#include "../utils/filesystem.h"
#include "../utils/plus.h"
#include "../utils/text.h"

/*
** {===========================================================================
** Macros and constants
*/

#if GBBASIC_COMPILER_ANALYZER_ENABLED
#	pragma message("Static analyzer enabled.")
#endif /* GBBASIC_COMPILER_ANALYZER_ENABLED */

/* ===========================================================================} */

/*
** {===========================================================================
** Static Analyzer
*/

namespace GBBASIC {

class StaticAnalyzerImpl : public StaticAnalyzer {
private:
	struct Result {
		Macro::List macrosDefinitions;
		Text::Array destinations;
		RamLocation::Dictionary ramAllocations;
		CodePageName::Array codePageNames;

		Result() {
		}
	};

private:
	AnalyzeHandler _analyzeHandler = nullptr; // Foreign.
	int _analyzing = 0;

	unsigned _languageDefinitionRevision = 1;
	Macro::List _macrosDefinitions;
	Text::Array _destinations;
	RamLocation::Dictionary _ramAllocations;
	CodePageName::Array _codePageNames;

public:
	StaticAnalyzerImpl(AnalyzeHandler analyzeHandler) : _analyzeHandler(analyzeHandler) {
	}
	virtual ~StaticAnalyzerImpl() override {
		_analyzeHandler = nullptr;
		_analyzing = 0;
	}

	virtual unsigned type(void) const override {
		return TYPE();
	}

	virtual bool clone(Object** ptr) const override { // Non-clonable.
		if (ptr)
			*ptr = nullptr;

		return false;
	}

	virtual bool analyzing(void) const override {
		return !!_analyzing;
	}
	virtual bool analyze(const Kernel* krnl, AssetsBundle::Ptr assets, AnalyzedHandler analyzed) override {
		++_analyzing;

		_analyzeHandler(
			std::bind(
				[this, krnl] (WorkTask* /* task */, AssetsBundle::Ptr assets) -> uintptr_t { // On work thread.
					Result* result = new Result();
					doAnalyze(result, krnl, assets);

					return (uintptr_t)result;
				},
				std::placeholders::_1, assets
			),
			[this] (WorkTask* /* task */, uintptr_t ptr) -> void { // On main thread.
				Result* result = (Result*)ptr;

				bool diff = false;
				if (!::equals(_macrosDefinitions, result->macrosDefinitions)) {
					_macrosDefinitions.clear();
					std::swap(_macrosDefinitions, result->macrosDefinitions);
					diff |= true;
				}

				if (!::equals(_destinations, result->destinations)) {
					_destinations.clear();
					std::swap(_destinations, result->destinations);
					_destinations.shrink_to_fit();
					diff |= true;
				}

				std::swap(_ramAllocations, result->ramAllocations);

				std::swap(_codePageNames, result->codePageNames);
				_codePageNames.shrink_to_fit();

				if (diff) {
					if (++_languageDefinitionRevision == 0)
						_languageDefinitionRevision = 1;
				}
			},
			[this, analyzed] (WorkTask* task, uintptr_t ptr) -> void { // On main thread.
				Result* result = (Result*)ptr;
				delete result;

				task->disassociated(true);

				if (analyzed)
					analyzed();

				--_analyzing;
			}
		);

		return true;
	}

	virtual unsigned getLanguegeDefinitionRevision(void) const override {
		return _languageDefinitionRevision;
	}

	virtual const Macro::List* getMacroDefinitions(void) const override {
		return &_macrosDefinitions;
	}

	virtual const Text::Array* getDestinitions(void) const override {
		return &_destinations;
	}

	virtual const RamLocation::Dictionary* getRamAllocations(void) const override {
		return &_ramAllocations;
	}

	virtual const CodePageName* getCodePageName(int page) const override {
		if (page < 0 || page >= (int)_codePageNames.size())
			return nullptr;

		return &_codePageNames[page];
	}

	virtual void clear(void) override {
		_languageDefinitionRevision = 1;
		_macrosDefinitions.clear();
		_destinations.clear();
		_ramAllocations.clear();
		_codePageNames.clear();
	}

private:
	static void doAnalyze(Result* result, const Kernel* krnl, const AssetsBundle::Ptr &assets) { // On work thread.
		// Prepare.
		std::string dir;
		Path::split(krnl->path(), nullptr, nullptr, &dir);
		const std::string rom = Path::combine(dir.c_str(), krnl->kernelRom().c_str());
		const std::string sym = Path::combine(dir.c_str(), krnl->kernelSymbols().c_str());
		const std::string aliases = Path::combine(dir.c_str(), krnl->kernelAliases().c_str());
		const int bootstrapBank = krnl->bootstrapBank();

		Program program;
		Options options;

		program.assets = assets;

		// Initialize the compiler options.
		options.rom = rom;
		options.sym = sym;
		options.aliases = aliases;
		options.passes = Options::Passes::GENERATE; // Only parse the source code and generate for the first pass.
		options.strategies.compatibility = Options::Strategies::Compatibilities::COLORED | Options::Strategies::Compatibilities::EXTENSION;
		options.strategies.bootstrapBank = bootstrapBank;
		options.piping.useWorkQueue = false;
		options.piping.lessConsoleOutput = true;

		// Initialize the output methods.
		options.onPrint = [] (const std::string &msg) -> void {
			fprintf(stdout, "[ANALYZER INFO] %s\n", msg.c_str());
		};
		options.onError = [&program] (const std::string &msg, bool isWarning, int page, int row, int column) -> void {
			std::string msg_;
			if (row != -1 || column != -1) {
				if (page != -1) {
					msg_ += "Page ";
					msg_ += Text::toPageNumber(page);
					msg_ += ", ";
				}
				msg_ += "Ln ";
				msg_ += Text::toString(row + 1);
				msg_ += ", col ";
				msg_ += Text::toString(column + 1 + program.lineNumberWidth);
				msg_ += ": ";
			}
			msg_ += msg;
			if (isWarning)
				fprintf(stderr, "[ANALYZER WARNING] %s\n", msg_.c_str());
			else
				fprintf(stderr, "[ANALYZER ERROR] %s\n", msg_.c_str());
		};

		// Compile.
		fprintf(stdout, "[ANALYZER INFO] Start analyzing.\n");

		const long long start = DateTime::ticks();

		const bool codeIsOk =
			   load(program, options) &&
			compile(program, options);
		(void)codeIsOk;

		doAnalyzeMacroDefinitions(result, program);

		doAnalyzeRamAllocations(result, program);

		doAnalyzeProgram(result, program);

		doAnalyzeCodePages(result, program);

		const long long end = DateTime::ticks();
		const long long diff = end - start;
		const double secs = DateTime::toSeconds(diff);
		const std::string msg = "[ANALYZER INFO] Analyzed in " + Text::toString(secs) + "s.\n";
		fprintf(stdout, msg.c_str());

		fprintf(stdout, "[ANALYZER INFO] End analyzing.\n");
	}
	static void doAnalyzeMacroDefinitions(Result* result, Program &program) {
		result->macrosDefinitions.clear();
		std::swap(result->macrosDefinitions, program.compiled.macros);
	}
	static void doAnalyzeRamAllocations(Result* result, Program &program) {
		result->ramAllocations.clear();
		std::swap(result->ramAllocations, program.compiled.allocations);
	}
	static void doAnalyzeProgram(Result* result, Program &program) {
		// Prepare.
		const INode::Ptr &root = program.root; // Get the compiled AST, which could be corrupt.
		if (!root)
			return;

		// Select root.
		Select prog = Select(root);

		// Select destinations.
		Select destinations = prog
			.children(Where(INode::Types::DESTINATION).doFailIfNotAllMatch(false).doRecursive(true));
		if (destinations.ok()) {
			destinations
				.foreach(
					[&] (const Select &, const INode::Ptr &dest, int) -> void {
						const INode::Abstract abs = dest->abstract();
						if (!abs.empty()) {
							std::string name = abs.front();
							Text::toLowerCase(name);
							result->destinations.push_back(name);
						}
					}
				);
		}
	}
	static void doAnalyzeCodePages(Result* result, Program &program) {
		// Prepare.
		const INode::Ptr &root = program.root; // Get the compiled AST, which could be corrupt.
		if (!root)
			return;

		// Select pages.
		Select pages = Select(root)
			.children(Where(INode::Types::PAGE));

		if (pages.ok()) {
			// Parse the code page names.
			result->codePageNames.resize(pages.count());
			pages
				.foreach(
					[&] (const Select &, const INode::Ptr &page, int index) -> void {
						Select dest = Select(page)
							.firstChild(Where(INode::Types::DESTINATION));
						if (!dest.ok())
							return;

						const INode::Abstract abs = dest->abstract();
						result->codePageNames[index] = CodePageName(abs.front());
					}
				);
		}
	}
};

StaticAnalyzer::CodePageName::CodePageName() {
}

StaticAnalyzer::CodePageName::CodePageName(const std::string &n) : name(n) {
}

StaticAnalyzer* StaticAnalyzer::create(AnalyzeHandler analyzeHandler) {
	StaticAnalyzerImpl* result = new StaticAnalyzerImpl(analyzeHandler);

	return result;
}

void StaticAnalyzer::destroy(StaticAnalyzer* ptr) {
	StaticAnalyzerImpl* impl = static_cast<StaticAnalyzerImpl*>(ptr);
	delete impl;
}

}

/* ===========================================================================} */
