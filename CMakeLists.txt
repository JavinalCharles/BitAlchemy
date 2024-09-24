cmake_minimum_required(VERSION 3.15)

project(
	BitAlchemy
	VERSION 0.1
	DESCRIPTION "A fast and lightweight C++ Game Engine library built on SDL2."
	LANGUAGES CXX
)

option(DEBUG "Enables DEBUG_MODE_ON Macro." ON)
option(DEBUG_VERBOSE "Enables DEBUG_VERBOSE_ENABLED" OFF)
option(BUILD_EXAMPLES "Instructs cmake to build the example programs as well, after building the library" OFF)

if(DEBUG)
add_compile_definitions(DEBUG_MODE_ON)
if(DEBUG_VERBOSE)
add_compile_definitions(DEBUG_VERBOSE_ENABLED)
endif()
endif()

set(SOURCES
	src/tinyxml2/tinyxml2.cpp
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
	src/BA/Exceptions/Inaccessible.cpp
	# src/BA/Generator/TileMapGenerator.cpp
	src/BA/Inputs/Input.cpp
	src/BA/Inputs/InputManager.cpp
	src/BA/Inputs/KeyboardInput.cpp
	src/BA/Inputs/MouseInput.cpp
	src/BA/Resources/Warehouse.cpp
	src/BA/Resources/Wrapper/Font.cpp
	src/BA/Resources/Wrapper/Music.cpp
	src/BA/Resources/Wrapper/Sound.cpp
	src/BA/Resources/Wrapper/Texture.cpp
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
	src/BA/Systems/VelocityWithCollisionSystem.cpp
	src/BA/Tools/DebugHelper.cpp
	src/BA/Utilities/Transform.cpp
	src/BA/Window/Window.cpp
	src/BA/Window/View.cpp
	src/BA/Globals.cpp
	src/BA/Engine.cpp
)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)
target_compile_options(compiler_flags INTERFACE 
	"$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wunused;-Wno-unused-parameter;-O2>"
)

add_library(BA STATIC ${SOURCES})

# set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

target_include_directories(BA
	PUBLIC
	${PROJECT_SOURCE_DIR}/include/
)

set(SDL_LIBS
	-lSDL2
	-lSDL2_image
	-lSDL2_mixer
	-lSDL2_ttf
)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	set(SDL_LIBS
		-lSDL2main
		${SDL_LIBS}
		-lwinmm -limm32 -lversion -lsetupapi
	)
	set(SDL_INCLUDE_DIRS
		${PROJECT_SOURCE_DIR}/deps/include
	)

	set(SDL_LIBRARY_DIRS
		${PROJECT_SOURCE_DIR}/deps/lib
	)
	include_directories(${SDL_INCLUDE_DIRS})
	link_directories(${SDL_LIBRARY_DIRS})
endif()
target_link_libraries(BA compiler_flags)


set(SAMPLES_INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include/
	${PROJECT_BINARY_DIR}
)





if (BUILD_EXAMPLES)
	if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
		add_compile_definitions(SDL_MAIN_HANDLED)
	endif()
	add_subdirectory(example)
endif()

# INSTALLATION
# if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
# message("${CMAKE_SYSTEM_PREFIX_PATH}")
# # install(DIRECTORY ${PROJECT_SOURCE_DIR}/dirs/ DESTINATION share)

# install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

# install(TARGETS BA DESTINATION lib)

# elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

# endif()
