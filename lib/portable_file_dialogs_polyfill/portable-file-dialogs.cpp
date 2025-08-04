#include "portable-file-dialogs.h"

namespace pfd {

open_file::open_file(
	std::string const &title,
	std::string const &default_path,
	std::vector<std::string> const &filters,
	opt options
) {
	(void)title;
	(void)default_path;
	(void)filters;
	(void)options;
}

open_file::open_file(
	std::string const &title,
	std::string const &default_path,
	std::vector<std::string> const &filters,
	bool allow_multiselect
) {
	(void)title;
	(void)default_path;
	(void)filters;
	(void)allow_multiselect;
}

std::vector<std::string> open_file::result() {
	return std::vector<std::string>();
}

save_file::save_file(
	std::string const &title,
	std::string const &default_path,
	std::vector<std::string> const &filters,
	opt options
) {
	(void)title;
	(void)default_path;
	(void)filters;
	(void)options;
}

save_file::save_file(
	std::string const &title,
	std::string const &default_path,
	std::vector<std::string> const &filters,
	bool confirm_overwrite
) {
	(void)title;
	(void)default_path;
	(void)filters;
	(void)confirm_overwrite;
}

std::string save_file::result() {
	return std::string();
}

select_folder::select_folder(
	std::string const &title,
	std::string const &default_path,
	opt options
) {
	(void)title;
	(void)default_path;
	(void)options;
}

std::string select_folder::result() {
	return std::string();
}

notify::notify(
	std::string const &title,
	std::string const &message,
	icon _icon
) {
	(void)title;
	(void)message;
	(void)_icon;
}

}
