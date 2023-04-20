set(SKELETON_SOURCES
	SkeletonEntity.cpp
	SkeletonScene.cpp
	main.cpp
)

add_executable(Skeleton ${SKELETON_SOURCES})

target_include_directories(Skeleton
	PUBLIC
	${SAMPLES_INCLUDE_DIRS}
)

target_link_libraries(Skeleton BA ${SDL_LIBS} compiler_flags)