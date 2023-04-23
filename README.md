# BitAlchemy
BitAlchemy is a free and open-source 2D game engine built on top of SDL2. BitAlchemy focuses on being fast and easy to use, making game development more accessible while giving you most of the tools you need to build and realize your games.

<sub>*BitAlchemy is currently still in development. While it is possible to make games with what we have now, there are still some APIs that need to be created before we can have a 1.0 release.*</sub>

## Dependencies
- **SDL2** - *As well as some other SDL2_* extersion libraries:*
  - `SDL2_image` 
  - `SDL2_mixer` 
  - `SDL2_ttf`
- **CMAKE `3.15+`** - For building and installing this library.

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
  - Text and Text display.
  - Map Generator
  - Simple A.I. behavior
  - Input Manager
    - ~~Keyboard Input~~
    - Mouse Input*
    - Window Events (Focus-in, Focus-out, Minimized, Maximized, Resized)
    - Joystic/Controller Input
  - A packaging system.
  - More example games/sample usage programs.

- <sub>*NOTE: The strikethroughed items are completed features.*</sub>
- <sub>* *partially completed.*</sub>

## Contributors
- Me (@JavinalCharles)

*There are a lot of things that needed to be done, even after the v1.0 release. If you've got some ideas or would like to contribute to this project, please don't hesitate to make a PR. All contributors will have their handle (or real name, if preferred) added to the contributor list no matter how big or small the contribution. Everything is appreciated. Thank you! :-D*
