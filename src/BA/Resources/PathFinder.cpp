#include <BA/Resources/PathFinder.hpp>

namespace fs = std::filesystem;
using ba::Resources::PathFinder;

std::vector<fs::path> ba::Resources::PathFinder::s_commonPaths{fs::current_path()};

PathFinder::PathFinder() = default;

PathFinder::~PathFinder() {
	m_paths.clear();
}

int PathFinder::addPath(const std::string& p) {
	return addPath(fs::path(p));
}

int PathFinder::addPath(const fs::path& p) {
	std::error_code ec;

	if (p.is_relative()) {
		int found = 0;
		for (const fs::path& cp : s_commonPaths) {
			fs::path canonP(cp / p);
			if (fs::exists(canonP, ec)) {
				found += addPath(canonP);
			}
		}
		if (found == 0) {
			std::cerr << "PathFinder encounters a relative path that is not a subpath of current directory or a subpath of any common search paths:" << p << std::endl;
		}
		return found;
	}

	fs::file_status status = fs::status(p, ec);
	if (ec.value() != 0) {
		std::cerr << "PathFinder is unable to obtain path status for path: " << p.c_str() << std::endl;
		std::cerr << "Error: " << ec.message() << std::endl;
		return false;
	}

	try {
		m_paths.push_back(p);
	}
	catch (const std::exception& e) {
		std::cerr << "PathFinder encountered an unknown error while adding path to search path: " << p.c_str() << std::endl;
		return false;
	}
	return true;
}

bool PathFinder::addCommonPath(const std::string& p) {
	return PathFinder::addCommonPath(fs::path(p));
}

bool PathFinder::addCommonPath(const fs::path& p) {
	std::error_code ec;
	if (p.is_relative()) {
		fs::path absoluteP(fs::absolute(p, ec));
		if (ec.value() != 0) {
			std::cerr << "Pathfinder encountered a relative path that cannot convert to absolute: " << p.c_str() << std::endl;
			std::cerr << "Error: " << ec.message() << std::endl;
			return false;
		}
		return addCommonPath(absoluteP);
	}

	fs::file_status stat = fs::status(p, ec);
	if (ec.value() != 0) {
		std::cerr << "PathFinder is unable to obtain path status for path: " << p.c_str() << std::endl;
		std::cerr << "Error: " << ec.message() << std::endl;
		return false;
	}

	if (!fs::exists(stat) || !fs::is_directory(stat) ) {
		std::cerr << "PathFinder::addCommonPath(); Could not add path: \"" << p.c_str() << "\". Either path does not exists or is not a directory." << std::endl;
		return false;
	}

	try {
		s_commonPaths.push_back(p);
	}
	catch (const std::exception& e) {
		std::cerr << "PathFinder encountered an unknown error while adding path to common search paths: " << p.c_str() << std::endl;
		return false;
	}

	return true;
}

std::optional<fs::path> PathFinder::findFile(const std::string& filePath) const {
	return findFile(fs::path(filePath));
}

std::optional<fs::path> PathFinder::findFile(const fs::path& filePath) const {
	std::error_code ec;
	if (!filePath.has_filename()) {
		return std::nullopt;
	}

	if (filePath.is_absolute()) {
		if (fs::exists(filePath, ec)) {
			return std::optional<fs::path>(filePath);
		}
		return std::nullopt;
	}

	for (const fs::path& path : m_paths) {
		fs::path p(path / filePath);
		if (fs::exists(p, ec)) {
			return std::optional<fs::path>(p);
		}
	}

	for (const fs::path& path : s_commonPaths) {
		fs::path p(path / filePath);
		if (fs::exists(p, ec)) {
			return std::optional<fs::path>(p);
		}
	}

	return std::nullopt;
}

std::vector<fs::path> PathFinder::findAllFiles(const std::string& filePath) const {
	return findAllFiles(fs::path(filePath));
}

std::vector<fs::path> PathFinder::findAllFiles(const fs::path& filePath) const {
	std::error_code ec;
	std::vector<fs::path> found;
	if (!filePath.has_filename()) {
		return found;
	}

	if (filePath.is_absolute()) {
		if (fs::exists(filePath, ec)) {
			found.push_back(filePath);
		}
		return found;
	}

	for (const fs::path& path : m_paths) {
		fs::path joined(path / filePath);
		if (fs::exists(joined, ec)) {
			found.push_back(joined);
		}
	}

	for (const fs::path& path : s_commonPaths) {
		fs::path joined(path / filePath);
		if (fs::exists(joined, ec)) {
			found.push_back(joined);
		}
	}

	return found;
}