#pragma once
#include <cstdint>
#include <cstddef>

namespace ba
{
	constexpr double PI = 3.14159265359;

	using int8 = 	std::int8_t;
	using uint8 = 	std::uint8_t;
	using int16 = 	std::int16_t;
	using uint16 = 	std::uint16_t;
	using int32 = 	std::int32_t;
	using uint32 = 	std::uint32_t;
	using int64 =	std::int64_t;
	using uint64 = 	std::uint64_t;

	using IDtype = 	std::size_t;

	enum ComponentID : IDtype {
		NONE = 0,
		A_I,
		ANIMATION,
		CAMERA,
		COLLIDABLE,
		COLLIDER,
		DRAWABLE,
		KEYBOARD_CONTROL,
		MOUSE_CONTROL,
		SOUND_EMITTER,
		TIMER,
		VELOCITY,
		XTRA1,
		XTRA2,
		XTRA3,
		XTRA4,
		XTRA5,
		XTRA6,
		XTRA7,
		XTRA8
	};

	enum ConfigID : IDtype {
		CONFIG_ROOT = 0,
		CONFIG_NEEDS_REWRITE,

		// Application Information
		ORG_NAME,
		APP_NAME,

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
} // namespace ba
