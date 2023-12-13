#pragma once

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <future>
#include "math.h"

#include "raylib.h"
#include "json.hpp"

constexpr float GRAVITY = 0.1f;
constexpr float TRAVERSESPEED = 3.0f;
constexpr float JUMPSPEED = -6.0f;
constexpr Vector2 STARTPOSITION = { 240.0f, 3194.0f };

enum SceneType { START_SCENE, MAIN_SCENE };

struct LevelTile { Vector2 position_on_screen; Rectangle spritesheet_position; };
struct ColliderTile { int id; Vector2 collider_position; };
struct Synapse { float input; float weight; };