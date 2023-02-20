cmake_minimum_required(VERSION 3.15)

project(
	BitAlchemy 
	VERSION 0.1
	DESCRIPTION "A fast and lightweight C++ Game Engine library built on SDL2."
	LANGUAGES CXX 
)

set(SOURCES 
	src/BA/Components/Component.cpp
	src/BA/Components/Drawable.cpp
	src/BA/Components/Sprite.cpp	
	src/BA/Components/Transformable.cpp
	src/BA/Entity/Entity.cpp
	src/BA/Systems/ComponentSystem.cpp
	src/BA/Systems/EntityManager.cpp
	src/BA/Utilities/Transform.cpp
	src/BA/Window/Window.cpp
	src/BA/Window/View.cpp
	src/BA/ResourceManager.cpp
)	

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

add_library(BA STATIC ${SOURCES})

target_include_directories(BA 
	PUBLIC 
	${PROJECT_SOURCE_DIR}/include/
)

target_link_libraries(BA SDL2 SDL2_image compiler_flags)

