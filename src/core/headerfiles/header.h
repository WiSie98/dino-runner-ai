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

constexpr float GRAVITY = 0.25f;

enum SceneType { START_SCENE, MAIN_SCENE };

struct LevelTile { Vector2 position_on_screen; Rectangle spritesheet_position; };
struct ColliderTile { int id; Vector2 collider_position; };
struct Synapse { float input; float weight; };