/*
** GB BASIC
**
** Copyright (C) 2023-2025 Tony Wang, all rights reserved
**
** For the latest info, see https://paladin-t.github.io/kits/gbb/
*/

#include "encoding.h"
#include "platform.h"
#include "../../lib/imgui_sdl/imgui_sdl.h"
#include <SDL.h>
#include <algorithm>
#include <clocale>

/*
** {===========================================================================
** Platform
*/

bool Platform::Transactions::empty(void) const {
	return ids.empty();
}

bool Platform::ignore(const char* path) {
	if (!path)
		return true;
	if (*path == '\0')
		return true;
	if (path[0] == '.' && path[1] == '\0')
		return true;
	if (path[0] == '.' && path[1] == '.' && path[2] == '\0')
		return true;

	return false;
}

std::string Platform::writableDirectory(void) {
	const char* cstr = SDL_GetPrefPath("gbbasic", "data");
	const std::string osstr = Unicode::toOs(cstr);
	SDL_free((void*)cstr);

	return osstr;
}

bool Platform::hasClipboardText(void) {
	return !!SDL_HasClipboardText();
}

std::string Platform::getClipboardText(void) {
	const char* cstr = SDL_GetClipboardText();
	const std::string txt = cstr;
	const std::string osstr = Unicode::toOs(txt);
	SDL_free((void*)cstr);

	return osstr;
}

void Platform::setClipboardText(const char* txt) {
	const std::string utfstr = Unicode::fromOs(txt);

	SDL_SetClipboardText(utfstr.c_str());
}

bool Platform::isLittleEndian(void) {
	union { uint32_t i; char c[4]; } bint = { 0x04030201 };

	return bint.c[0] == 1;
}

const char* Platform::locale(const char* loc) {
	const char* result = setlocale(LC_ALL, loc);
	fprintf(
		stdout,
		"Set generic locale to \"%s\".\n",
		result ? result : "nil"
	);

	return result;
}

static Platform::Languages _locale = Platform::Languages::UNSET;

Platform::Languages Platform::locale(void) {
	return _locale;
}

void Platform::locale(Languages lang) {
	_locale = lang;
}

void Platform::idle(void) {
	SDL_Event evt;
	if (SDL_PollEvent(&evt)) {
		const bool windowResized = evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_SIZE_CHANGED;
		const bool targetReset = evt.type == SDL_RENDER_TARGETS_RESET;
		if (windowResized || targetReset)
			ImGuiSDL::Reset();
	}
}

int Platform::cpuCount(void) {
	return SDL_GetCPUCount();
}

/* ===========================================================================} */
