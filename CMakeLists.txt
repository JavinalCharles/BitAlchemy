cmake_minimum_required(VERSION 3.15)

project(
	BitAlchemy 
	VERSION 0.1
	DESCRIPTION "A fast and lightweight C++ Game Engine library built on SDL2."
	LANGUAGES CXX 
)

set(SOURCES 
	src/BA/Components/AI/AI.cpp
	src/BA/Components/AI/ProgrammedAI.cpp
	src/BA/Components/Camera.cpp
	src/BA/Components/Colliders/BoxCollider.cpp
	src/BA/Components/Colliders/Collider.cpp
	src/BA/Components/Animation.cpp
	src/BA/Components/Component.cpp
	src/BA/Components/Collidable.cpp
	src/BA/Components/Drawable.cpp
	src/BA/Components/FunctionalCollidable.cpp
	src/BA/Components/KeyboardControl.cpp
	src/BA/Components/MouseControl.cpp
	src/BA/Components/Sprite.cpp
	src/BA/Components/Timer.cpp
	src/BA/Components/Velocity.cpp
	src/BA/Components/SoundEmitter.cpp
	src/BA/Components/Text.cpp
	src/BA/Entities/Entity.cpp
	src/BA/Entities/Transformable.cpp
	src/BA/Generator/TileMapGenerator.cpp
	src/BA/Inputs/Input.cpp
	src/BA/Inputs/InputManager.cpp
	src/BA/Inputs/KeyboardInput.cpp
	src/BA/Inputs/MouseInput.cpp
	src/BA/Scenes/BitAlchemySplash.cpp
	src/BA/Scenes/Scene.cpp
	src/BA/Scenes/SceneManager.cpp
	src/BA/Systems/AISystem.cpp
	src/BA/Systems/AnimationSystem.cpp
	src/BA/Systems/CameraSystem.cpp
	src/BA/Systems/CollisionSystem.cpp
	src/BA/Systems/ComponentSystem.cpp
	src/BA/Systems/EntityManager.cpp
	src/BA/Systems/KeyboardControlSystem.cpp
	src/BA/Systems/MouseControlSystem.cpp
	src/BA/Systems/MovementSystem.cpp
	src/BA/Systems/MusicPlayer.cpp
	src/BA/Systems/RenderSystem.cpp
	src/BA/Systems/SoundSystem.cpp
	src/BA/Systems/TimerSystem.cpp
	src/BA/Utilities/Transform.cpp
	src/BA/Window/Window.cpp
	src/BA/Window/View.cpp
	src/BA/ResourceManager.cpp
	src/BA/Engine.cpp
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
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused;-O3>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

add_library(BA STATIC ${SOURCES})

target_include_directories(BA 
	PUBLIC 
	${PROJECT_SOURCE_DIR}/include/
)

set(SAMPLES_INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include/
	${PROJECT_BINARY_DIR}
)

set(SDL_LIBS
	SDL2
	SDL2_image
	SDL2_mixer
	SDL2_ttf
)

add_subdirectory(samples)

target_link_libraries(BA compiler_flags)

# INSTALLATION
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
message("${CMAKE_SYSTEM_PREFIX_PATH}")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/dirs/ DESTINATION share)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

install(TARGETS BA DESTINATION lib)

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

endif()
