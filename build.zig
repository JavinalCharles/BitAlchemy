const std = @import("std");

const ExampleExecutableParameters = struct {
    name: []const u8,
    srcDir: []const u8,
    srcFiles: []const []const u8,
};

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const buildExamples = b.option(bool, "buildExamples", "an option to compile, link and build the provided example programs.");

    const libBA = b.addStaticLibrary(.{
        .name = "BA",
        .target = target,
        .optimize = optimize,
    });

    const sourceFiles: [48][]const u8 = [_][]const u8{
        "src/BA/Components/AI/AI.cpp",
        "src/BA/Components/AI/ProgrammedAI.cpp",
        "src/BA/Components/Camera.cpp",
        "src/BA/Components/Colliders/BoxCollider.cpp",
        "src/BA/Components/Colliders/Collider.cpp",
        "src/BA/Components/Animation.cpp",
        "src/BA/Components/Component.cpp",
        "src/BA/Components/Collidable.cpp",
        "src/BA/Components/Drawable.cpp",
        "src/BA/Components/FunctionalCollidable.cpp",
        "src/BA/Components/KeyboardControl.cpp",
        "src/BA/Components/MouseControl.cpp",
        "src/BA/Components/Sprite.cpp",
        "src/BA/Components/Timer.cpp",
        "src/BA/Components/Velocity.cpp",
        "src/BA/Components/SoundEmitter.cpp",
        "src/BA/Components/Text.cpp",
        "src/BA/Entities/Entity.cpp",
        "src/BA/Entities/Transformable.cpp",
        "src/BA/Exceptions/Inaccessible.cpp",
        "src/BA/Generator/TileMapGenerator.cpp",
        "src/BA/Inputs/Input.cpp",
        "src/BA/Inputs/InputManager.cpp",
        "src/BA/Inputs/KeyboardInput.cpp",
        "src/BA/Inputs/MouseInput.cpp",
        "src/BA/Scenes/BitAlchemySplash.cpp",
        "src/BA/Scenes/Scene.cpp",
        "src/BA/Scenes/SceneManager.cpp",
        "src/BA/Systems/AISystem.cpp",
        "src/BA/Systems/AnimationSystem.cpp",
        "src/BA/Systems/CameraSystem.cpp",
        "src/BA/Systems/CollisionSystem.cpp",
        "src/BA/Systems/ComponentSystem.cpp",
        "src/BA/Systems/EntityManager.cpp",
        "src/BA/Systems/KeyboardControlSystem.cpp",
        "src/BA/Systems/MouseControlSystem.cpp",
        "src/BA/Systems/MovementSystem.cpp",
        "src/BA/Systems/MusicPlayer.cpp",
        "src/BA/Systems/RenderSystem.cpp",
        "src/BA/Systems/SoundSystem.cpp",
        "src/BA/Systems/TimerSystem.cpp",
        "src/BA/Systems/VelocityWithCollisionSystem.cpp",
        "src/BA/Tools/DebugHelper.cpp",
        "src/BA/Utilities/Transform.cpp",
        "src/BA/Window/Window.cpp",
        "src/BA/Window/View.cpp",
        "src/BA/ResourceManager.cpp",
        "src/BA/Engine.cpp",
    };

    const flags: [5][]const u8 = [_][]const u8{
        "-std=c++20",
        "-Wall",
        "-Wextra",
        "-Wshadow",
        "-Wunused",
    };

    libBA.addCSourceFiles(.{ 
		.files = &sourceFiles, 
		.flags = &flags 
	});

    libBA.linkLibCpp();

	libBA.addIncludePath(.{ 
		.cwd_relative = "include" 
	});

	if (target.result.os.tag == .linux) {
		libBA.linkSystemLibrary("SDL2");
	}
	else {
		libBA.addIncludePath(.{.cwd_relative = "deps/SDL2-2.30.6/i686-w64-mingw32/include"});
		libBA.addIncludePath(.{.cwd_relative = "deps/SDL2_image-2.8.2/i686-w64-mingw32/include"});
		libBA.addIncludePath(.{.cwd_relative = "deps/SDL2_mixer-2.8.0/i686-w64-mingw32/include"});
		libBA.addIncludePath(.{.cwd_relative = "deps/SDL2_ttf-2.22.0/i686-w64-mingw32//include"});
		libBA.addIncludePath(.{.cwd_relative = "deps/rapidxml"});

		b.installBinFile("deps/SDL2-2.30.6/i686-w64-mingw32/lib/libSDL2.a", "libSDL2.a");
		b.installBinFile("deps/SDL2_image-2.8.2/i686-w64-mingw32/lib/libSDL2_image.a", "libSDL2_image.a");
		b.installBinFile("deps/SDL2_mixer-2.8.0/i686-w64-mingw32/lib/libSDL2_mixer.a", "libSDL2_mixer.a");
		b.installBinFile("deps/SDL2_ttf-2.22.0/i686-w64-mingw32/lib/libSDL2_ttf.a", "libSDL2_ttf.a");
	}

    b.installArtifact(libBA);
    b.installDirectory(.{ .source_dir = .{ .cwd_relative = "include/BA/" }, .install_dir = .header, .install_subdir = "BA/" });

    if (buildExamples != true) {
        // Everything beyond this point is about building the
        // example programs. If user goals is merely to nuild the
        // library, function execution should end here.
        return;
    }

    const executables = &[_]ExampleExecutableParameters{ 
		.{ 
			.name = "Line", 
			.srcDir = "example/Line", 
			.srcFiles = &.{ 
				"LineScene.cpp", 
				"main.cpp" 
			} 
		}, 
		.{ 
			.name = "SDL_Files", 
			.srcDir = "example/RandomTests", 
			.srcFiles = &.{
				"SDL_Files.cpp"
			} 
		}, 
		.{ 
			.name = "Skeleton", 
			.srcDir = "example/Skeleton", .srcFiles = &.{ 
				"BlueCharEntity.cpp", 
				"SkeletonEntity.cpp", 
				"SkeletonScene.cpp", 
				"main.cpp" 
			} 
		}, 
		.{ 
			.name = "TestMap", 
			.srcDir = "example/TestMap", 
			.srcFiles = &.{ 
				"TestMapScene.cpp", 
				"main.cpp" 
			} 
		}, 
		.{ 
			.name = "Text", 
			.srcDir = "example/Text", 
			.srcFiles = &.{ 
				"TextScene.cpp", 
				"main.cpp" 
			} 
		} 
	};

	for (executables) |exeParam| {
		const exe = b.addExecutable(.{
			.name = exeParam.name,
			.target = target,
			.optimize = optimize
		});

		exe.addCSourceFiles(.{
			.root = .{
				.cwd_relative = exeParam.srcDir
			},
			.files = exeParam.srcFiles,
			.flags = &flags
		});
		exe.addIncludePath(.{.cwd_relative = "include/"});
		exe.addIncludePath(.{ .cwd_relative = exeParam.srcDir });

		exe.linkLibCpp();
		exe.linkLibrary(libBA);
		exe.linkSystemLibrary("SDL2");
		exe.linkSystemLibrary("SDL2_image");
		exe.linkSystemLibrary("SDL2_mixer");
		exe.linkSystemLibrary("SDL2_ttf");

		b.installArtifact(exe);
	}
}
