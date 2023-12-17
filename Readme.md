```
 __      __       _   _           _   _____  _       _    __                                          _____ 
 \ \    / /      | | (_)         | | |  __ \| |     | |  / _|                                   /\   |_   _|
  \ \  / /__ _ __| |_ _  ___ __ _| | | |__) | | __ _| |_| |_ ___  _ __ _ __ ___   ___ _ __     /  \    | |  
   \ \/ / _ \ '__| __| |/ __/ _` | | |  ___/| |/ _` | __|  _/ _ \| '__| '_ ` _ \ / _ \ '__|   / /\ \   | |  
    \  /  __/ |  | |_| | (_| (_| | | | |    | | (_| | |_| || (_) | |  | | | | | |  __/ |     / ____ \ _| |_ 
     \/ \___|_|   \__|_|\___\__,_|_| |_|    |_|\__,_|\__|_| \___/|_|  |_| |_| |_|\___|_|    /_/    \_\_____|
                                                                                                            
                                                                                                            
```

# Vertical Platformer AI - Made with Raylib in C++

[![CMakeBuilds](https://github.com/chfhhd/raylibstarter-minimal/actions/workflows/cmake.yml/badge.svg)](https://github.com/chfhhd/raylibstarter/actions/workflows/cmake.yml)

Made by: WiSie98 `https://github.com/WiSie98` and THEGRANDNICK `https://github.com/THEGRANDNICK`

This vertical platformer ai includes a doodle jump like game with an ai which uses a neural network with a genetic algorithm which was created with the RayLib library.

![Screenshot (7)](https://user-images.githubusercontent.com/100346454/211833451-76660a5c-1eeb-4d7b-8925-4b1760ea0f73.png)

This project was created as part of an exam during our studies to learn the basics of machine learning.
We used the raylib-minimal template which was provided by `https://github.com/chfhhd` and used the `https://github.com/nlohmann/json` parser to parse the levels form the json format into c++.

The spritesheets where made by the user `chipmunk` from `https://opengameart.org/content/metroid-like`.

![vertical_platformer_game_preview](https://github.com/WiSie98/vertical-platformer-ai/assets/100346454/70307f47-9a6b-4a8b-b2a2-c80e59b3b862)
![vertical_platformer_debug_preview](https://github.com/WiSie98/vertical-platformer-ai/assets/100346454/012872f2-e208-4784-b209-5f690d6d6001)


## Usage

You need to download or clone this repository into your prefered IDE. The raylib library will be downloaded automatically by CMake. To start the project you need to select the `main.cpp` as the start element, which is located under `src`.

### Controlls

- Use the `space bar` to skip a generation.
- To display the collision boxes press `1`.
- To visualize the detection box of the ai actors press `2`.

If you want to play the game as a playable charachter, go to `header.h` under `src/core/headerfiles` and change `STARTASPLAYER` to true.

```
constexpr bool STARTASPLAYER = true;
```

- The player character can be controlled with the `WAS` or `Arrow keys`.
- You can jump with `W` or `Arrow Up` and move left and right with `A` or `Arrow Left` and `D` or `Arrow Right`.

Some other useful setting can be found in `header.h` which is located under `src/core/headerfiles`.

![vertical_platformer_headerfile_preview](https://github.com/WiSie98/vertical-platformer-ai/assets/100346454/7f446f1d-915e-4a7f-9fd5-438608e77690)

### Choose a different raylib version

Which raylib version is used can be specified in the `cmake/raylib.cmake` file. If this is changed after CMake has already created the project once, you must use CMake to completely rebuild the project.

## License

see `LICENCE` file for details.
