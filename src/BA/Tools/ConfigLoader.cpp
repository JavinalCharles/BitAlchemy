#include "BA/Tools/ConfigLoader.hpp"

namespace ba {

ConfigMap loadDefaultConfigurations() {
	ConfigMap defaultConfig = {
		{WINDOW_WIDTH, 768u},
		{WINDOW_HEIGHT, 768u},
		{WINDOW_FULLSCREEN, 0u},
		{WINDOW_BORDERLESS, 0u},
		{WINDOW_RESIZABLE, 0u},
		{WINDOW_TITLE, ""},

		{MOUSE_ENABLED, true},
		{KEYBOARD_ENABLED, true},
		{CONTROLLER_ENABLED, false},

		{MOUSE_SCROLL_SPEED, 50u},

		{GENERAL_VOLUME, 75u},
		{MUSIC_VOLUME, 75u},
		{SFX_VOLUME, 75u},
		{VOICE_VOLUME, 75u},
		{AUDIO_TYPE, 1u},

		{BRIGHTNESS_LEVEL, 75u},
		{GAMMA_LEVEL, 75u},
		{CONTRAST_LEVEL, 75u},
		{VSYNC_ENABLED, 0u},

		{FPS_CAP_LIMIT, 120u}
	};

	return defaultConfig;
}

} // namespace ba
