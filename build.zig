const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

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

    const flags: [6][]const u8 = [6][]const u8{
        "-std=c++20",
        "-Wall",
        "-Wextra",
        "-Wshadow",
        "-Wformat=2",
        "-Wunused",
    };

    libBA.addCSourceFiles(.{ .files = &sourceFiles, .flags = &flags });
    libBA.linkLibC();
    libBA.linkLibCpp();
    libBA.addIncludePath(.{ .cwd_relative = "include/" });

    b.installArtifact(libBA);
}
