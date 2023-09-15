# BitAlchemy
BitAlchemy is a free and open-source 2D game engine built on top of SDL2. BitAlchemy focuses on being fast and easy to use, making game development more accessible while giving you most of the tools you need to build and realize your games.

<sub>*BitAlchemy is currently still in development. While it is possible to make games with what we have now, there are still some APIs that need to be created before we can have a 1.0 release.*</sub>

## Dependencies
- **SDL2** - *As well as some other SDL2_* extersion libraries:*
	- `SDL2_image` 
	- `SDL2_mixer` 
	- `SDL2_ttf`
- **CMAKE `3.15+`** - For building and installing this library.
- **RapidXML `1.13`** - Used for reading .tmx and .tsx files created by Tiled.

## Example

### Displaying a sprite
```
// display_sprite.cpp
#include <BA/BitAlchemy.hpp>

int main() {
	ba::Engine engine();

	// Define engine behavior upon game initialization.
	engine.onInit([&engine]() {
		// Create a Scene. Almost everything in BA is within a scene.
		std::shared_ptr<ba::GenericLevelScene> scene = engine.createScene<ba::GenericLevelScene>();
		
		// Create an entity using the scene.
		std::shared_ptr<Entity> e = scene.createEntity();
		e->setPosition(32, 32); // (x, y) coordinates
		// Add a component
		auto sprite = e->addComponent<ba::Sprite>();
		sprite->loadFromFile("sprite.png");

		// Add the entity to the scene.
		scene->addEntity(e);

		// adds the scene to the engine and load it.
		engine.addScene(scene);
	});

	// Initialize the engine.
	engine.init();

	// Start the game loop.
	engine.run();

	// After game loop ends, clean up resources.
	engine.cleanUp();

	return 0;
}
```

## Building and Installing

#### STEP 1
- First, clone this repository and navigate to the BitAlchemy folder then create a build directory and cd into it. You can use the following command:
	- $`mkdir build && cd build/`
#### STEP 2
- Then execute the following set of commands. It will tell cmake to prepare and compile the source files and build a BA library. It will also compile and link some of the sample programs provided with the library. *(Note: In Unix, actually running the sample programs might need installation first as these programs needed the assets in `dirs/` folder to be in the relevant `share/bit-alchemy/assets` directory.)*
	- $`cmake ..`
	- $`cmake --build .`
#### STEP 3
- After that, you can now install the library as well as the header to the relvant `include/` `lib/` system directories using the following command.
	- $`cmake --build . --target install`

	- *If it doesn't work, you can try it with `sudo` instead:*
	- $`sudo cmake --build . --target install`

## Development Progress
- *v1.0 Release Goals:*
	- ~~Basic Collision System~~
	- ~~A Sprite and Animation system~~
	- ~~Scene Manager~~
	- ~~Music Player~~
	- ~~Sound Effects System~~
	- ~~Text and Text display.~~
	- ~~Map Generator~~
	- ~~Simple A.I. behavior~~
	- Input Manager*
		- ~~Keyboard Input~~
		- ~~Mouse Input~~
		- Window Events (Focus-in, Focus-out, Minimized, Maximized, Resized)
  	- A saving system 
	- A packaging system.
	- More example games/sample usage programs.*

- <sub>*NOTE: The strikethroughed items are completed features.*</sub>
- <sub>* - *partially completed.*</sub>

## Contributors
- Me (@JavinalCharles)

*There are a lot of things that needed to be done, even after the v1.0 release. If you've got some ideas or would like to contribute to this project, please don't hesitate to make a PR. All contributors will have their handle (or real name, if preferred) added to the contributor list no matter how big or small the contribution. Everything is appreciated. Thank you! :-D*
