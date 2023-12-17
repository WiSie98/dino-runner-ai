#pragma once

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <future>
#include <tuple>
#include "math.h"

#include "raylib.h"
#include "json.hpp"

constexpr Vector2 GRIDSIZE = { 17.0f, 12.0f };													//Sets the detection grid for the AIs (higher number means a slower calculation time).

//AI related constants
constexpr bool STARTASPLAYER = false;															//Starts the game with a playable character.
constexpr int NUMOFAI = 20;																		//Sets the total number of AI.
constexpr int NUMINPUTS = static_cast<int>(GRIDSIZE.x) * static_cast<int>(GRIDSIZE.y);			//Sets the number of inputs based on the detection grid size.
constexpr int NUMHIDDEN = 20;																	//Sets the number of hidden neurons in the hidden layer.
constexpr int NUMOUTPUTS = 4;																	//Sets the number of outputs (more outputs need to be coded into the actor_ai aiMovement() function).
constexpr int TIMEPERGENERATION = 1200;															//Sets the time after whitch it changes the generation (1 = 1 Frame | 60 frames = 1 second).
constexpr float BIAS = 0.01f;																	//Sets the bias whitch gets calculated on each neuron.
constexpr float MUTATIONRATE = 0.05f;															//Sets the mutation rate for the genetic algorithm (0.05 = 5%).
constexpr float MINWEIGHT = -1.0f;																//Sets the minimum weight for each connection between neurons.
constexpr float MAXWEIGHT = 1.0f;																//Sets the maximum weight for each connection between neurons.
constexpr float DEATHPENALTY = 5.0f;															//Sets the death penalty score for the fitness function.

constexpr float GRAVITY = 0.1f;																	//Sets the gravity for the game environment.
constexpr float TRAVERSESPEED = 3.0f;															//Sets the traverse speed for each character.
constexpr float JUMPSPEED = -6.0f;																//Sets the jump speed for each charachter.
constexpr float TILESIZE = 16.0f;																//Sets the tile size for tile width and hight.
constexpr Vector2 STARTPOSITION = { 240.0f, 3194.0f };											//Sets the startposition of all charachters and the camera.

enum SceneType { START_SCENE, MAIN_SCENE };

struct LevelTile { Vector2 position_on_screen; Rectangle spritesheet_position; };
struct ColliderTile { int id; Vector2 collider_position; };
struct Synapse { float input; float weight; };