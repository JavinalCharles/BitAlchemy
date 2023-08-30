set(SDL_FILES_TEST_SOURCES
	SDL_Files.cpp
)

add_executable(SDL_Files_Test ${SDL_FILES_TEST_SOURCES})

target_include_directories(SDL_Files_Test
	PUBLIC
	${SAMPLES_INCLUDE_DIRS}
)

target_link_libraries(SDL_Files_Test BA ${SDL_LIBS} compiler_flags)
