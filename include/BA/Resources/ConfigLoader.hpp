#pragma once

#include <any>
#include <unordered_map>
#include <BA/Resources/PathFinder.hpp>

namespace fs = std::filesystem;

namespace ba {

namespace Resources {

class ConfigLoader : public ba::Resources::PathFinder {
public:
	ConfigLoader();
	explicit ConfigLoader(const std::string& configFile);
	explicit ConfigLoader(const fs::path& configPath);

	void loadConfig(const std::string& configFile);
	void loadConfig(const fs::path& configPath);

	std::any at(const std::string& key);
	const std::any at(const std::string& key) const;

	template <typename T>
	inline bool cast(const std::string& key);

private:
	std::unordered_map<std::string&, std::any> m_configMap;
	fs::path m_configFilePath;
}; // class ConfigLoader

} // namespace Resources
} // namespace ba