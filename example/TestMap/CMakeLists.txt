set(TEST_MAP_SOURCES
	TestMapScene.cpp
	main.cpp
)

add_executable(TestMap ${TEST_MAP_SOURCES})

target_include_directories(TestMap
	PUBLIC
	${SAMPLES_INCLUDE_DIRS}
)

target_link_libraries(TestMap BA ${SDL_LIBS} compiler_flags)
