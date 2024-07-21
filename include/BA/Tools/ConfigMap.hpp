#pragma once

#include "BA/Types.hpp"

namespace ba {

enum ConfigID : IDtype {
	CONFIG_ROOT = 0,
	CONFIG_NEEDS_REWRITE,

	// Application Information
	ORG_NAME,
	APP_NAME,
	PREF_PATH,

	// User Information
	PROFILE_NAME,

	// window configuration
	WINDOW_WIDTH,
	WINDOW_HEIGHT,
	WINDOW_FULLSCREEN,
	WINDOW_BORDERLESS,
	WINDOW_RESIZABLE,
	WINDOW_TITLE,

	// input configuraions
	MOUSE_ENABLED,
	KEYBOARD_ENABLED,
	CONTROLLER_ENABLED,

	// mouse input configuration
	MOUSE_SCROLL_SPEED,

	// volume configuration
	GENERAL_VOLUME,
	MUSIC_VOLUME,
	SFX_VOLUME,
	VOICE_VOLUME,
	AUDIO_TYPE,

	// display configurations
	BRIGHTNESS_LEVEL,
	GAMMA_LEVEL,
	CONTRAST_LEVEL,
	VSYNC_ENABLED,

	// Game Play Settings
	FPS_CAP_LIMIT,
};

class ConfigMap {
public:
	ConfigMap();
	ConfigMap(ConfigMap&) = delete;
	ConfigMap(ConfigMap&&) = delete;

	ConfigMap(const std::string& organization, const std::string& application);

	//////////////////////////////////////////////////////////////////////////
	// GAME CONFIGURATION
	//////////////////////////////////////////////////////////////////////////
	/**
	 * Sets the selected configuration with a value.
	 * @param id the ID of the configuration to set
	 * @param value the new value of the selected configuration.
	 */
	void setConfig(ConfigID id, std::any value);

	/**
	 * Gets the value of the selected configuration. 
	 * @returns A reference to the configuration value.
	 * @{
	 */
	const std::any& at(ConfigID) const;
	const std::any& at(const ConfigID) const;
	std::any& operator[](ConfigID);
	std::any& operator[](const ConfigID);
	/** @} */
private:
	void loadDefaultConfigurations();

	/**
	 * Loads Configuration File (if any) and parses the data to the map.
	 * 	If no configuration file is found, it will attempt to create one with
	 * default configuration
	 */
	void loadConfigFile();

private:
	bool m_appIsUsingConfigFile = false;

	std::map<ConfigID, std::any> m_configMap;
};


} // namespace ba
