#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/scene.h"

class MainScene final : public Scene {
public:

	MainScene();

	~MainScene();

	void update(ActorPlayer& player, MainCamera& camera) override;
	void draw(ActorPlayer& player, MainCamera& camera) override;
	SceneType setNextScene(ActorPlayer& player, bool& exitWindowRequested) override;

	void drawBackground(MainCamera& camera);
	void drawForeground(MainCamera& camera);

	void parseLevelBackgroundTiles(nlohmann::json& tileset_description, nlohmann::json& level_map);
	void parseLevelForegroundTiles(nlohmann::json& tileset_description, nlohmann::json& level_map);
	void parseLevelCollider(nlohmann::json& tileset_description, nlohmann::json& level_map);

	void detectCollision(ActorPlayer& player, MainCamera& camera);

private:

	Texture2D tile_atlas_texture;
	LevelTile woodland_tiles;

	std::vector<std::shared_ptr<LevelTile>> background_vector;
	std::vector<std::shared_ptr<LevelTile>> foreground_vector;
	std::vector<std::shared_ptr<ColliderTile>> collider_vector;

};