set(TEXT_SAMPLE_SOURCES
	TextScene.cpp
	main.cpp
)

add_executable(Text ${TEXT_SAMPLE_SOURCES})

target_include_directories(Text
	PUBLIC
	${SAMPLES_INCLUDE_DIRS}
)

target_link_libraries(Text BA ${SDL_LIBS} compiler_flags)
