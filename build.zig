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

	// const libBA = b.addSharedLibrary(.{
	// 	.name = "BA",
	// 	.target = target,
	// 	.optimize = optimize
	// });

    const libBA = b.addStaticLibrary(.{
        .name = "BA",
        .target = target,
        .optimize = optimize,
    });

    const sourceFiles: [47][]const u8 = [_][]const u8{
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
        // "src/BA/Generator/TileMapGenerator.cpp",
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
		libBA.addIncludePath(.{.cwd_relative = "deps/include"});
		libBA.addLibraryPath(.{.cwd_relative = "deps/lib"});

		b.installBinFile("deps/lib/SDL2.dll", "SDL2.dll");
		b.installBinFile("deps/lib/SDL2_image.dll", "SDL2_image.dll");
		b.installBinFile("deps/lib/SDL2_mixer.dll", "SDL2_mixer.dll");
		b.installBinFile("deps/lib/SDL2_ttf.dll", "SDL2_ttf.dll");
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
		// .{ 
		// 	.name = "TestMap", 
		// 	.srcDir = "example/TestMap", 
		// 	.srcFiles = &.{ 
		// 		"TestMapScene.cpp", 
		// 		"main.cpp" 
		// 	} 
		// }, 
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
		exe.linkSystemLibrary("SDL2");
		if (target.result.os.tag == .windows) {
			exe.linkSystemLibrary("SDL2main");
		}
		exe.linkSystemLibrary("SDL2_image");
		exe.linkSystemLibrary("SDL2_mixer");
		exe.linkSystemLibrary("SDL2_ttf");
		if (target.result.os.tag == .windows) {
			exe.linkSystemLibrary("kernel32");
			exe.linkSystemLibrary("user32");
			exe.linkSystemLibrary("gdi32");
			exe.linkSystemLibrary("opengl32");
			exe.linkSystemLibrary("winmm");
			exe.linkSystemLibrary("dxguid");
		}
		exe.linkLibrary(libBA);

		b.installArtifact(exe);
	}
}
