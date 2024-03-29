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
} // namespace ba
