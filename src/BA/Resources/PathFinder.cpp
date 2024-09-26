#include <BA/Resources/PathFinder.hpp>

namespace fs = std::filesystem;
using ba::Resources::PathFinder;

std::vector<fs::path> ba::Resources::PathFinder::s_commonPaths{fs::current_path()};

PathFinder::PathFinder() = default;

PathFinder::~PathFinder() {
	clear();
}

int PathFinder::addPath(const std::string& p) {
	return addPath(fs::path(p));
}

int PathFinder::addPath(const fs::path& p) {
	std::error_code ec;
	int found = 0;

	if (p.is_relative()) [[likely]] {
		for (const fs::path& cp : s_commonPaths) {
			fs::path canonP(cp / p);
			if (fs::exists(canonP, ec) && fs::is_directory(canonP, ec)) {
				try {
					m_paths.push_back(canonP);
				}
				catch (const std::exception& e) {
					continue;
				}
				++found;
			}
		}
		if (found == 0) {
			std::cerr << "PathFinder encounters a relative path that is not a subpath of current directory or a subpath of any common search paths:" << p << std::endl;
		}
		return found;
	} // else if p is an absolute path.
	else if (fs::exists(p, ec) && fs::is_directory(p, ec)) {
		++found;
		try {
			m_paths.push_back(p);
		}
		catch (const std::exception& e) {
			--found;
		}
	}
	return found;
}

bool PathFinder::addCommonPath(const std::string& p) {
	return PathFinder::addCommonPath(fs::path(p));
}

bool PathFinder::addCommonPath(const fs::path& p) {
	std::error_code ec;
	if (p.is_relative()) {
		fs::path absoluteP(fs::canonical(p, ec));
		if (ec.value() != 0) {
			std::cerr << "Pathfinder encountered a relative path that cannot convert to absolute: " << p.c_str() << std::endl;
			std::cerr << "Error: " << ec.message() << std::endl;
			return false;
		}
		try {
			s_commonPaths.push_back(absoluteP);
		}
		catch (const std::exception& e) {
			return false;
		}
		return true;
	}

	if (!fs::exists(p, ec) || !fs::is_directory(p, ec) ) {
		std::cerr << "PathFinder error. Absolute paths must lead to an existing directory.\npath: " << p << std::endl;
		if (ec.value() != 0) {
			std::cerr << ec.message() << std::endl;
		}
		return false;
	}

	try {
		s_commonPaths.push_back(p);
	}
	catch (const std::exception& e) {
		std::cerr << "PathFinder caught an exception." << std::endl;
		std::cerr << e.what() << std::endl;
		return false;
	}

	return true;
}

std::optional<fs::path> PathFinder::findFile(const std::string& filePath) const {
	return findFile(fs::path(filePath));
}

std::optional<fs::path> PathFinder::findFile(const fs::path& filePath) const {
	if (!filePath.has_filename()) {
		return std::nullopt;
	}

	std::error_code ec;

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
	std::vector<fs::path> found;
	if (!filePath.has_filename()) {
		return found;
	}

	std::error_code ec;

	if (filePath.is_absolute()) {
		if (fs::exists(filePath, ec)) {
			try {
				found.push_back(filePath);
			}
			catch (std::exception& e) {
				std::cerr << "PathFinder caught an exception." << std::endl;
				std::cerr << e.what() << std::endl;
			}
		}
		return found;
	}

	for (const fs::path& path : m_paths) {
		fs::path joined(path / filePath);
		if (fs::exists(joined, ec)) {
			try {
				found.push_back(joined);
			}
			catch (const std::exception& e) {
				std::cerr << "PathFinder caught an exception." << std::endl;
				std::cerr << e.what() << std::endl;
			}
		}
	}

	for (const fs::path& path : s_commonPaths) {
		fs::path joined(path / filePath);
		if (fs::exists(joined, ec)) {
			try {
				found.push_back(joined);
			}
			catch (const std::exception& e) {
				std::cerr << "PathFinder caught an exception." << std::endl;
				std::cerr << e.what() << std::endl;
			}
		}
	}

	return found;
}

void PathFinder::clear() {
	m_paths.clear();
}