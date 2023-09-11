#include "BA/Tools/ConfigLoader.hpp"

namespace ba {

ConfigMap loadDefaultConfigurations(const std::u16string& orgName, const std::u16string& gameName) {
	ConfigMap defaultConfig = {
		{ORGANIZATION_NAME, orgName},
		{GAME_NAME, gameName},

		{WINDOW_WIDTH, u"768"},
		{WINDOW_HEIGHT, u"768"},
		{WINDOW_FULLSCREEN, u"0"},
		{WINDOW_BORDERLESS, u"0"},
		{WINDOW_RESIZABLE, u"0"},
		{WINDOW_TITLE, orgName + u" | " + gameName},

		{MOUSE_ENABLED, u"1"},
		{KEYBOARD_ENABLED, u"1"},
		{CONTROLLER_ENABLED, u"0"},

		{MOUSE_SCROLL_SPEED, u"50"},

		{GENERAL_VOLUME, u"75"},
		{MUSIC_VOLUME, u"75"},
		{SFX_VOLUME, u"75"},
		{VOICE_VOLUME, u"75"},
		{AUDIO_TYPE, u"Stereo"},

		{BRIGHTNESS_LEVEL, u"75"},
		{GAMMA_LEVEL, u"75"},
		{CONTRAST_LEVEL, u"75"},
		{VSYNC_ENABLED, u"0"}
	};

	return defaultConfig;
}

} // namespace ba
