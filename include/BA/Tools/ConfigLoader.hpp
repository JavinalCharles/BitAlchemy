#pragma once

#include <any>
#include <map>
#include <string>

#include "BA/ResourceManager.hpp"
#include "BA/Types.hpp"

namespace ba {
	enum ConfigID : ba::uint32 {
		CONFIG_ROOT = 0,

		// meta-data
		ORGANIZATION_NAME,
		GAME_NAME,

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

	using ConfigMap = std::map<ConfigID, std::any>;

	ConfigMap loadDefaultConfigurations(const std::u16string& orgName = u"", const std::u16string& gameName = u"");

	// ConfigMap loadConfigurationsFromFile(const std::u16string& fileName, ResourceManager* resources);

	// void saveConfiguration(const ConfigMap& configMap, const std::u16string& fileName);
} // namespace ba
