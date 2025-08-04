// Doesn't implement anything but only helps to compile.
// See "lib/portable_file_dialogs/portable-file-dialogs.h" for more details.

#include <string>
#include <vector>

#pragma once

namespace pfd {

enum class opt : unsigned char {
	none = 0,
	multiselect     = 0x1,
	force_overwrite = 0x2,
	force_path      = 0x4
};
inline opt operator | (opt a, opt b) { return opt(uint8_t(a) | uint8_t(b)); }
inline bool operator & (opt a, opt b) { return bool(uint8_t(a) & uint8_t(b)); }

enum class icon {
	info = 0,
	warning,
	error,
	question
};

class open_file {
public:
	open_file(
		std::string const &title,
		std::string const &default_path = "",
		std::vector<std::string> const &filters = { "All Files", "*" },
		opt options = opt::none
	);
	open_file(
		std::string const &title,
		std::string const &default_path,
		std::vector<std::string> const &filters,
		bool allow_multiselect
	);

	std::vector<std::string> result();
};

class save_file {
public:
	save_file(
		std::string const &title,
		std::string const &default_path = "",
		std::vector<std::string> const &filters = { "All Files", "*" },
		opt options = opt::none
	);
	save_file(
		std::string const &title,
		std::string const &default_path,
		std::vector<std::string> const &filters,
		bool confirm_overwrite
	);

	std::string result();
};

class select_folder {
public:
	select_folder(
		std::string const &title,
		std::string const &default_path = "",
		opt options = opt::none
	);

	std::string result();
};

class notify {
public:
	notify(
		std::string const &title,
		std::string const &message,
		icon _icon = icon::info
	);
};

}
