#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/scene.h"

class MainScene final : public Scene {
public:

	MainScene();

	~MainScene();

	void update(ActorPlayer& player, std::vector<ActorAI>& ai_vector, MainCamera& camera) override;
	void draw(ActorPlayer& player, std::vector<ActorAI>& ai_vector, MainCamera& camera) override;
	SceneType setNextScene(ActorPlayer& player, std::vector<ActorAI>& ai_vector, bool& exitWindowRequested) override;

	void drawBackground(MainCamera& camera);
	//void drawForeground(MainCamera& camera);

	void parseLevelBackgroundTiles(nlohmann::json& tileset_description, nlohmann::json& level_map);
	//void parseLevelForegroundTiles(nlohmann::json& tileset_description, nlohmann::json& level_map);
	void parseLevelCollider(nlohmann::json& tileset_description, nlohmann::json& level_map);

	void detectPlayerCollision(ActorPlayer& player, MainCamera& camera);
	void detectAICollision(ActorAI& ai);

private:

	Texture2D tile_atlas_texture;
	LevelTile woodland_tiles;

	std::vector<std::shared_ptr<LevelTile>> background_vector;
	std::vector<std::shared_ptr<LevelTile>> foreground_vector;
	std::vector<std::shared_ptr<ColliderTile>> collider_vector;

};