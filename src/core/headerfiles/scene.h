#pragma once

#include "header.h"
#include "camera.h"
#include "../../actors/headerfiles/actor_player.h"
#include "../../actors/headerfiles/actor_ai.h"

class Scene {

public:

	void setSceneType(SceneType scene_type);
	SceneType getSceneType();

	virtual void update(ActorPlayer& player, std::vector<ActorAI>& ai_vector, MainCamera& camera) = 0;
	virtual void draw(ActorPlayer& player, std::vector<ActorAI>& ai_vector, MainCamera& camera) = 0;

	virtual SceneType setNextScene(ActorPlayer& player, std::vector<ActorAI>& ai_vector, bool& exitWindowRequested) = 0;

private:

protected:

	SceneType scene_type = START_SCENE;

};