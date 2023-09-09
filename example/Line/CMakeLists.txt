set(LINE_SOURCES
	LineScene.cpp
	main.cpp
)

add_executable(Line ${LINE_SOURCES})

target_include_directories(Line
	PUBLIC
	${SAMPLES_INCLUDE_DIRS}
)

target_link_libraries(Line BA ${SDL_LIBS} compiler_flags)
