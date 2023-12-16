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

//AI related constants
constexpr bool STARTASPLAYER = false;
constexpr int NUMOFAI = 100;
constexpr int NUMINPUTS = 5;
constexpr int NUMHIDDEN = 9;
constexpr int NUMOUTPUTS = 4;
constexpr int TIMEPERGENERATION = 1800; //1 = 1 Frame
constexpr float MUTATIONRATE = 0.1f;
constexpr float MINWEIGHT = -1.0f;
constexpr float MAXWEIGHT = 1.0f;
constexpr float DEATHPENALTY = 10.0f;

constexpr float GRAVITY = 0.1f;
constexpr float TRAVERSESPEED = 3.0f;
constexpr float JUMPSPEED = -6.0f;
constexpr Vector2 STARTPOSITION = { 240.0f, 3194.0f };

enum SceneType { START_SCENE, MAIN_SCENE };

struct LevelTile { Vector2 position_on_screen; Rectangle spritesheet_position; };
struct ColliderTile { int id; Vector2 collider_position; };
struct Synapse { float input; float weight; };
struct Output { int iterator; float output; };