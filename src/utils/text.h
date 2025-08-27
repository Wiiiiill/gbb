/*
** GB BASIC
**
** Copyright (C) 2023-2025 Tony Wang, all rights reserved
**
** For the latest info, see https://paladin-t.github.io/kits/gbb/
*/

#ifndef __TEXT_H__
#define __TEXT_H__

#include "../gbbasic.h"
#include "mathematics.h"
#include "object.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>

/*
** {===========================================================================
** Text
*/

/**
 * @brief Text object and utilities.
 */
class Text : public virtual Object {
public:
	typedef std::shared_ptr<Text> Ptr;

	typedef std::vector<std::string> Array;
	typedef std::list<std::string> List;
	typedef std::map<std::string, std::string> Dictionary;
	typedef std::set<std::string> Set;

public:
	GBBASIC_CLASS_TYPE('T', 'E', 'X', 'T')

	virtual const std::string &text(void) const = 0;
	virtual std::string &text(void) = 0;
	virtual void text(const std::string &txt) = 0;
	virtual void clear(void) = 0;

	static void locale(const char* loc);

	/**
	 * @param[in, out] str
	 */
	static size_t toLowerCase(char* str, size_t len);
	/**
	 * @param[in, out] str
	 */
	static size_t toLowerCase(std::string &str);
	/**
	 * @param[in, out] str
	 */
	static size_t toUpperCase(char* str, size_t len);
	/**
	 * @param[in, out] str
	 */
	static size_t toUpperCase(std::string &str);

	/**
	 * @param[out] val
	 */
	static bool fromString(const std::string &str, bool &val);
	/**
	 * @param[out] val
	 */
	static bool fromString(const std::string &str, Int32 &val);
	/**
	 * @param[out] val
	 */
	static bool fromString(const std::string &str, UInt32 &val);
	/**
	 * @param[out] val
	 */
	static bool fromString(const std::string &str, Int64 &val);
	/**
	 * @param[out] val
	 */
	static bool fromString(const std::string &str, UInt64 &val);
	/**
	 * @param[out] val
	 */
	static bool fromString(const std::string &str, Single &val);
	/**
	 * @param[out] val
	 */
	static bool fromString(const std::string &str, Double &val);

	/**
	 * @param[out] val
	 */
	static bool fromHexCharacter(char ch, UInt8 &val);

	static std::string toString(Int32 val, int width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0), bool fixed = false);
	static std::string toString(UInt32 val, int width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0), bool fixed = false);
	static std::string toString(Int64 val, int width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0), bool fixed = false);
	static std::string toString(UInt64 val, int width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0), bool fixed = false);
	static std::string toString(Single val, int precision = 6, int width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));
	static std::string toString(Double val, int precision = 6, int width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));
	static std::string toString(bool val, bool yesNo = false);
	static std::string toString(Int32 val, bool fixed);
	static std::string toString(UInt32 val, bool fixed);
	static std::string toString(Int64 val, bool fixed);
	static std::string toString(UInt64 val, bool fixed);

	static std::string toBin(Int8 val);
	static std::string toBin(UInt8 val);
	static std::string toBin(Int16 val);
	static std::string toBin(UInt16 val);
	static std::string toBin(Int32 val);
	static std::string toBin(UInt32 val);
	static std::string toBin(Int64 val);
	static std::string toBin(UInt64 val);

	static std::string toHex(Int32 val, int width = sizeof(Int32) * 2, char fill = '0', bool toupper = false);
	static std::string toHex(UInt32 val, int width = sizeof(UInt32) * 2, char fill = '0', bool toupper = false);
	static std::string toHex(Int64 val, int width = sizeof(Int64) * 2, char fill = '0', bool toupper = false);
	static std::string toHex(UInt64 val, int width = sizeof(UInt64) * 2, char fill = '0', bool toupper = false);
	static std::string toHex(Int32 val, bool toupper);
	static std::string toHex(UInt32 val, bool toupper);
	static std::string toHex(Int64 val, bool toupper);
	static std::string toHex(UInt64 val, bool toupper);

	static std::string toPageNumber(int val);

	static std::string toScaledBytes(Int64 val);

	static std::string toNumberWithCommas(const std::string &str);

	static std::string toVariableName(const std::string &str);
	static std::string pascalToSnake(const std::string &str);
	static std::string snakeToPascal(const std::string &str);

	static std::string remove(const std::string &str, const std::string &charsToRemove);
	static std::string trim(const std::string &str, const std::string &delims = " \f\n\r\t\v");
	static std::string trimLeft(const std::string &str, const std::string &delims = " \f\n\r\t\v");
	static std::string trimRight(const std::string &str, const std::string &delims = " \f\n\r\t\v");
	static std::string limitLeft(const std::string &txt, int width);
	static std::string limitRight(const std::string &txt, int width);
	static std::string padLeft(const std::string &txt, int width, char fill = ' ');
	static std::string padRight(const std::string &txt, int width, char fill = ' ');
	static std::string replace(const std::string &str, const std::string &from, const std::string &to, bool all = true);
	static std::string join(const Array &array, const std::string &sep);
	static Array split(const std::string &str, const std::string &delims, bool parseUpToNext = true, size_t maxSplits = 0);
	static Array tokenise(const std::string &str, const std::string &singleDelims, const std::string &doubleDelims, bool parseUpToNext, size_t maxSplits = 0);
	/**
	 * @param[out] txt
	 */
	static bool postfix(const std::string &str, std::string &txt, int &num);
	static std::string repeat(const std::string &str, int count);

	static size_t indexOf(const std::string &str, char what, size_t start = 0);
	static size_t indexOf(const std::string &str, const std::string &what, size_t start = 0);
	static size_t lastIndexOf(const std::string &str, char what, size_t start = std::string::npos);
	static size_t lastIndexOf(const std::string &str, const std::string &what, size_t start = std::string::npos);
	static int indexOf(const Array &arr, const std::string &what);

	static bool startsWith(const char* str, const char* what, bool caseInsensitive);
	static bool startsWith(const std::string &str, const std::string &what, bool caseInsensitive);
	static bool endsWith(const std::string &str, const std::string &what, bool caseInsensitive);
	static bool matchWildcard(const std::string &str, const char* wildcard, bool caseInsensitive);
	static size_t count(const std::string &str, const char what);

	static const char* styleOf(const std::string &str);
	/**
	 * @param[in, out] str
	 */
	static void stylish(std::string &str, const char* dst, const char* src = nullptr);

	static std::string cformat(const char* fmt, ...);
	static std::string format(const std::string &fmt, const std::string &arg, int index = 0);
	static std::string format(const std::string &fmt, const Variant &arg, int index = 0);
	static std::string format(const std::string &fmt, const Array &args, int index = 0);
	static std::string format(const std::string &fmt, const std::initializer_list<std::string> &args, int index = 0);

	/**
	 * @param[out] endptr
	 */
	static long strtol(char const* str, char** endptr, int base);
	/**
	 * @param[out] endptr
	 */
	static long long strtoll(char const* str, char** endptr, int base);
	/**
	 * @param[out] endptr
	 */
	static unsigned long long strtoull(char const* str, char** endptr, int base);
	/**
	 * @param[out] endptr
	 */
	static double strtod(const char* str, char** endptr);

	static Text* create(void);
	static void destroy(Text* ptr);
};

/* ===========================================================================} */

#endif /* __TEXT_H__ */
