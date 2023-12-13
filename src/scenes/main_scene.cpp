#include "headerfiles/main_scene.h"

MainScene::MainScene() {
	setSceneType(MAIN_SCENE);

	std::ifstream tileset_description_file("./assets/levels/vp_ts_metroidlevel.json");
	nlohmann::json tileset_description = nlohmann::json::parse(tileset_description_file);
	tileset_description_file.close();

	std::ifstream level_map_file("./assets/levels/vp_lv_metroidlevel.json");
	nlohmann::json level_map = nlohmann::json::parse(level_map_file);
	level_map_file.close();

	this->tile_atlas_texture = LoadTexture(("./assets/graphics/tilesets/" + tileset_description["image"].get<std::string>()).c_str());

	parseLevelBackgroundTiles(tileset_description, level_map);
	//parseLevelForegroundTiles(tileset_description, level_map);
	parseLevelCollider(tileset_description, level_map);
}

MainScene::~MainScene() {}

void MainScene::update(ActorPlayer& player, std::vector<ActorAI>& ai_vector, MainCamera& camera) {
	Vector2 vec = {STARTPOSITION.x, 0};
	if (player.getIsActive()) {
		player.update();
		detectPlayerCollision(player, camera);
		//detectAICollision(ai_vector, camera);
		camera.setTarget(player.getCurrentPosition());
	} else {
		for (int i = 0; i < ai_vector.size() - 1; i++) {
			if (vec.y < ai_vector[i].getCurrentPosition().y) {
				vec.y = ai_vector[i].getCurrentPosition().y;
			}
		}
		camera.setTarget(vec);
	}

	for (int i = 0; i < ai_vector.size() - 1; i++) {
		ai_vector[i].setIsStanding(GetRandomValue(0, 1));
		ai_vector[i].setNearestPlatformEdge(GetRandomValue(-256, 256));
		ai_vector[i].setNearestPlatformDistance(GetRandomValue(-512, 512));
		ai_vector[i].setNearestPlatformBeneathDistance(GetRandomValue(-1024, 1024));
		ai_vector[i].update();
	}

}

void MainScene::draw(ActorPlayer& player, std::vector<ActorAI>& ai_vector, MainCamera& camera) {
	BeginMode2D(camera.getMainCamera());
	drawBackground(camera);
	if (player.getIsActive()) {
		player.draw();
	}

	for (int i = 0; i < ai_vector.size() - 1; i++) {
		ai_vector[i].draw();
	}

	EndMode2D();
}

SceneType MainScene::setNextScene(ActorPlayer& player, std::vector<ActorAI>& ai_vector, bool& exitWindowRequested) {

	if (IsKeyPressed(KEY_BACKSPACE)) {
		return START_SCENE;
	}
	else if (IsKeyPressed(KEY_ESCAPE)) {
		exitWindowRequested = true;
	}

	return MAIN_SCENE;
}

//---------------------------Functions---------------------------------

void MainScene::drawBackground(MainCamera& camera) {
	Vector2 camera_position = camera.getMainCamera().target;
	camera_position.x = camera_position.x - static_cast<float>(GetScreenWidth() / 2);
	camera_position.y = camera_position.y - static_cast<float>(GetScreenHeight() / 2);
	for (const auto& tile : this->background_vector) {
		if (camera_position.x < tile->position_on_screen.x && tile->position_on_screen.x < camera_position.x + static_cast<float>(GetScreenWidth()) && camera_position.y < tile->position_on_screen.y && tile->position_on_screen.y < camera_position.y + static_cast<float>(GetScreenHeight())) {
			DrawTextureRec(this->tile_atlas_texture, tile->spritesheet_position, tile->position_on_screen, WHITE);
		}
	}

	if (IsKeyDown(KEY_ONE)) {
		for (const auto& tile : this->collider_vector) {
			if (camera_position.x < tile->collider_position.x && tile->collider_position.x < camera_position.x + static_cast<float>(GetScreenWidth()) && camera_position.y < tile->collider_position.y && tile->collider_position.y < camera_position.y + static_cast<float>(GetScreenHeight())) {
				switch (tile->id)
				{
				case 0:
					DrawRectangle(tile->collider_position.x, tile->collider_position.y, 16, 16, RED);
					break;
				case 1:
					DrawRectangle(tile->collider_position.x, tile->collider_position.y, 16, 16, GREEN);
					break;
				case 2:
					DrawRectangle(tile->collider_position.x, tile->collider_position.y, 16, 16, BLUE);
					break;
				default:
					break;
				}
			}
		}
	}
}

/*
void MainScene::drawForeground(MainCamera& camera) {
	Vector2 camera_position = camera.getMainCamera().target;
	camera_position.x = camera_position.x - static_cast<float>(GetScreenWidth() / 2);
	camera_position.y = camera_position.y - static_cast<float>(GetScreenHeight() / 2);
	for (const auto& tile : this->foreground_vector) {
		if (camera_position.x < tile->position_on_screen.x && tile->position_on_screen.x < camera_position.x + static_cast<float>(GetScreenWidth()) && camera_position.y < tile->position_on_screen.y && tile->position_on_screen.y < camera_position.y + static_cast<float>(GetScreenHeight())) {
			DrawTextureRec(this->tile_atlas_texture, tile->spritesheet_position, tile->position_on_screen, WHITE);
		}
	}
}
*/

void MainScene::parseLevelBackgroundTiles(nlohmann::json& tileset_description, nlohmann::json& level_map) {

	Vector2 vec = { 0, 0 };
	Rectangle rec = { 0, 0, level_map["tilewidth"], level_map["tileheight"] };

	for (auto const& layer : level_map["layers"]) {
		if (layer["type"] == "tilelayer" && layer["visible"]) {
			for (auto const& tileId : layer["data"]) {
				if (layer["id"] < 3) {
					if (tileId != 0) {
						rec.x = static_cast<float>(((static_cast<int>(tileId) -1) % static_cast<int>(tileset_description["columns"]))) * static_cast<float>(level_map["tilewidth"]);
						rec.y = static_cast<float>(floor(static_cast<float>(tileId) / static_cast<float>(tileset_description["columns"]))) * static_cast<float>(level_map["tilewidth"]);
						
						if (static_cast<int>(tileId) % 20 == 0) {
							rec.y -= 16;
						}

						std::shared_ptr<LevelTile> tile = std::make_shared<LevelTile>();
						tile->position_on_screen = vec;
						tile->spritesheet_position = rec;
						this->background_vector.push_back(tile);
					}
				}
				else {
					return;
				}

				vec.x += static_cast<float>(level_map["tilewidth"]);
				if (vec.x >= static_cast<float>(layer["width"]) * static_cast<float>(level_map["tilewidth"])) {
					vec.x = 0;
					vec.y += static_cast<float>(level_map["tileheight"]);
				}
				if (vec.y >= static_cast<float>(layer["height"]) * static_cast<float>(level_map["tileheight"])) {
					vec.y = 0;
				}
			}
		}

	}
}

/*void MainScene::parseLevelForegroundTiles(nlohmann::json& tileset_description, nlohmann::json& level_map) {
	Vector2 vec = { 0, 0 };
	Rectangle rec = { 0, 0, level_map["tilewidth"], level_map["tileheight"] };

	for (auto const& layer : level_map["layers"]) {
		if (layer["type"] == "tilelayer" && layer["visible"]) {
			for (auto const& tileId : layer["data"]) {
				if (layer["id"] > 8 && layer["id"] != 13) {
					if (tileId != 0) {
						rec.x = static_cast<float>(((static_cast<int>(tileId) - 1) % static_cast<int>(tileset_description["columns"]))) * static_cast<float>(level_map["tilewidth"]);
						rec.y = static_cast<float>(floor(static_cast<float>(tileId) / static_cast<float>(tileset_description["columns"]))) * static_cast<float>(level_map["tilewidth"]);
						if (static_cast<int>(tileId) % 32 == 0) {
							rec.y -= 16;
						}

						std::shared_ptr<LevelTile> tile = std::make_shared<LevelTile>();
						tile->position_on_screen = vec;
						tile->spritesheet_position = rec;
						this->foreground_vector.push_back(tile);
					}
				}

				vec.x += static_cast<float>(level_map["tilewidth"]);
				if (vec.x >= static_cast<float>(layer["width"]) * static_cast<float>(level_map["tilewidth"])) {
					vec.x = 0;
					vec.y += static_cast<float>(level_map["tileheight"]);
				}
				if (vec.y >= static_cast<float>(layer["height"]) * static_cast<float>(level_map["tileheight"])) {
					vec.y = 0;
				}
			}
		}

	}
}*/

void MainScene::parseLevelCollider(nlohmann::json& tileset_description, nlohmann::json& level_map) {
	Vector2 vec = { 0, 0 };
	Rectangle rec = { 0, 0, level_map["tilewidth"], level_map["tileheight"] };

	for (auto const& layer : level_map["layers"]) {
		if (layer["type"] == "tilelayer" && layer["id"] == 3) {
			for (auto const& tileId : layer["data"]) {
				if (tileId != 0) {
					std::shared_ptr<ColliderTile> collider_tile = std::make_shared<ColliderTile>();
					collider_tile->id = 0;
					collider_tile->collider_position = vec;
					this->collider_vector.push_back(collider_tile);
				}

				vec.x += static_cast<float>(level_map["tilewidth"]);
				if (vec.x >= static_cast<float>(layer["width"]) * static_cast<float>(level_map["tilewidth"])) {
					vec.x = 0;
					vec.y += static_cast<float>(level_map["tileheight"]);
				}
				if (vec.y >= static_cast<float>(layer["height"]) * static_cast<float>(level_map["tileheight"])) {
					vec.y = 0;
				}
			}
		}

	}
	for (auto const& layer : level_map["layers"]) {
		if (layer["type"] == "tilelayer" && layer["id"] == 4) {
			for (auto const& tileId : layer["data"]) {
				if (tileId != 0) {
					std::shared_ptr<ColliderTile> collider_tile = std::make_shared<ColliderTile>();
					collider_tile->id = 1;
					collider_tile->collider_position = vec;
					this->collider_vector.push_back(collider_tile);
				}

				vec.x += static_cast<float>(level_map["tilewidth"]);
				if (vec.x >= static_cast<float>(layer["width"]) * static_cast<float>(level_map["tilewidth"])) {
					vec.x = 0;
					vec.y += static_cast<float>(level_map["tileheight"]);
				}
				if (vec.y >= static_cast<float>(layer["height"]) * static_cast<float>(level_map["tileheight"])) {
					vec.y = 0;
				}
			}
		}

	}

	for (auto const& layer : level_map["layers"]) {
		if (layer["type"] == "tilelayer" && layer["id"] == 5) {
			for (auto const& tileId : layer["data"]) {
				if (tileId != 0) {
					std::shared_ptr<ColliderTile> collider_tile = std::make_shared<ColliderTile>();
					collider_tile->id = 2;
					collider_tile->collider_position = vec;
					this->collider_vector.push_back(collider_tile);
				}

				vec.x += static_cast<float>(level_map["tilewidth"]);
				if (vec.x >= static_cast<float>(layer["width"]) * static_cast<float>(level_map["tilewidth"])) {
					vec.x = 0;
					vec.y += static_cast<float>(level_map["tileheight"]);
				}
				if (vec.y >= static_cast<float>(layer["height"]) * static_cast<float>(level_map["tileheight"])) {
					vec.y = 0;
				}
			}
		}

	}
}

void MainScene::detectPlayerCollision(ActorPlayer& player, MainCamera& camera) {

	bool is_collision = false;
	Vector2 camera_position = camera.getMainCamera().target;
	camera_position.x = camera_position.x - static_cast<float>(GetScreenWidth() / 2);
	camera_position.y = camera_position.y - static_cast<float>(GetScreenHeight() / 2);

	Rectangle player_rec = { player.getCurrentPosition().x, player.getCurrentPosition().y, 16, 32 };
	Rectangle collider_rec = { 0, 0, 16, 16 };
	for (const auto& tile : this->collider_vector) {

		collider_rec.x = tile->collider_position.x;
		collider_rec.y = tile->collider_position.y;

		if (camera_position.x < collider_rec.x && collider_rec.x < camera_position.x + static_cast<float>(GetScreenWidth()) && camera_position.y < collider_rec.y && collider_rec.y < camera_position.y + static_cast<float>(GetScreenHeight())) {
			if (tile->id == 0 || tile->id == 1) {
				if (CheckCollisionRecs(player_rec, collider_rec)) {
					if (tile->collider_position.y < player.getCurrentPosition().y) { //Test if the platform is above the player
						player.setJumpVelocity(0);
						player.setCurrentPosition(player.getLastPosition());
					} else if (tile->collider_position.y > player.getCurrentPosition().y + 32 || tile->collider_position.y + 16 > player.getCurrentPosition().y + 32) { //Test if the platform is under the player
						player.setJumpVelocity(0);
						player.setCurrentPosition(player.getCurrentPosition().x, tile->collider_position.y - 32);
						player.setIsStanding(true);
					} else if (tile->collider_position.x < player.getCurrentPosition().x || tile->collider_position.x > player.getCurrentPosition().x + 16) { //Test if the platform is at the sides the player
						player.setIsStanding(false);
						player.setCurrentPosition(player.getLastPosition());
					}
					is_collision = true;
				} else if (is_collision == false) {
					player.setIsStanding(false);
				}
			} else if (tile->id == 2) {
				if (CheckCollisionRecs(player_rec, collider_rec)) {
					player.setIsDead(true);
				}
			}
		}
	}
	player.setLastPosition(player.getCurrentPosition());
}

/*void detectAICollision(std::vector<ActorAI>& ai_vector, MainCamera& camera) {

	bool is_collision = false;
	Vector2 camera_position = camera.getMainCamera().target;
	camera_position.x = camera_position.x - static_cast<float>(GetScreenWidth() / 2);
	camera_position.y = camera_position.y - static_cast<float>(GetScreenHeight() / 2);

	Rectangle player_rec = { player.getCurrentPosition().x, player.getCurrentPosition().y, 16, 32 };
	Rectangle collider_rec = { 0, 0, 16, 16 };
	for (const auto& tile : this->collider_vector) {

		collider_rec.x = tile->collider_position.x;
		collider_rec.y = tile->collider_position.y;

		if (camera_position.x < collider_rec.x && collider_rec.x < camera_position.x + static_cast<float>(GetScreenWidth()) && camera_position.y < collider_rec.y && collider_rec.y < camera_position.y + static_cast<float>(GetScreenHeight())) {
			if (tile->id == 0 || tile->id == 1) {
				if (CheckCollisionRecs(player_rec, collider_rec)) {
					if (tile->collider_position.y < player.getCurrentPosition().y) { //Test if the platform is above the player
						player.setJumpVelocity(0);
						player.setCurrentPosition(player.getLastPosition());
					}
					else if (tile->collider_position.y > player.getCurrentPosition().y + 32 || tile->collider_position.y + 16 > player.getCurrentPosition().y + 32) { //Test if the platform is under the player
						player.setJumpVelocity(0);
						player.setCurrentPosition(player.getCurrentPosition().x, tile->collider_position.y - 32);
						player.setIsStanding(true);
					}
					else if (tile->collider_position.x < player.getCurrentPosition().x || tile->collider_position.x > player.getCurrentPosition().x + 16) { //Test if the platform is at the sides the player
						player.setIsStanding(false);
						player.setCurrentPosition(player.getLastPosition());
					}
					is_collision = true;
				}
				else if (is_collision == false) {
					player.setIsStanding(false);
				}
			}
			else if (tile->id == 2) {
				if (CheckCollisionRecs(player_rec, collider_rec)) {
					player.setIsDead(true);
				}
			}
		}
	}
	player.setLastPosition(player.getCurrentPosition());
}*/