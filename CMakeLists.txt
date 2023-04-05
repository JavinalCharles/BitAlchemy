cmake_minimum_required(VERSION 3.15)

project(
	BitAlchemy 
	VERSION 0.1
	DESCRIPTION "A fast and lightweight C++ Game Engine library built on SDL2."
	LANGUAGES CXX 
)

set(SOURCES 
	src/BA/Components/Colliders/BoxCollider.cpp
	src/BA/Components/Colliders/Collider.cpp
	src/BA/Components/Animation.cpp
	src/BA/Components/Component.cpp
	src/BA/Components/Drawable.cpp
	src/BA/Components/KeyboardControl.cpp
	src/BA/Components/Sprite.cpp
	src/BA/Components/Velocity.cpp
	src/BA/Entities/Entity.cpp
	src/BA/Entities/Transformable.cpp
	src/BA/Systems/AnimationSystem.cpp
	src/BA/Systems/CollisionSystem.cpp
	src/BA/Systems/ComponentSystem.cpp
	src/BA/Systems/EntityManager.cpp
	src/BA/Systems/InputManager.cpp
	src/BA/Systems/KeyboardControlSystem.cpp
	src/BA/Systems/MovementSystem.cpp
	src/BA/Systems/RenderSystem.cpp
	src/BA/Utilities/Transform.cpp
	src/BA/Window/Window.cpp
	src/BA/Window/View.cpp
	src/BA/ResourceManager.cpp
	src/BA/Engine.cpp
)

set(SOURCE_ANIMATION_SAMPLE
	samples/Animation/SkeletonEntity.cpp
	samples/Animation/main.cpp
)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

option(DEBUG "Enables DEBUG_MODE_ON Macro." ON)
option(DEBUG_VERBOSE "Enables DEBUG_VERBOSE_ENABLED" OFF)

if(DEBUG)
add_compile_definitions(DEBUG_MODE_ON)
if(DEBUG_VERBOSE)
add_compile_definitions(DEBUG_VERBOSE_ENABLED)
endif()
endif()

target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

add_library(BA STATIC ${SOURCES})

add_executable(sample ${SOURCE_ANIMATION_SAMPLE})


target_include_directories(BA 
	PUBLIC 
	${PROJECT_SOURCE_DIR}/include/
)

target_include_directories(sample 
	PUBLIC
	${PROJECT_SOURCE_DIR}/include/
	${PROJECT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/samples/Animation/
)

target_link_libraries(BA SDL2 SDL2_image SDL2_ttf compiler_flags)
target_link_libraries(sample BA SDL2 SDL2_image SDL2_ttf compiler_flags)
