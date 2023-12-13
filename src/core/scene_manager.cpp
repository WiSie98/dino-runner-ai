#include "headerfiles/scene_manager.h"

SceneManager::SceneManager() {}

//---------------------------Functions---------------------------------

void SceneManager::switchToScene(SceneType scene_type) {
	for (const auto& scene : this->scenes) {
		if (scene->getSceneType() == scene_type) {
			this->current_scene = scene;
		}
	}
}

void SceneManager::update(ActorPlayer& player, std::vector<ActorAI>& ai_vector, MainCamera& camera) {
	this->current_scene->update(player, ai_vector, camera);
}

void SceneManager::draw(ActorPlayer& player, std::vector<ActorAI>& ai_vector, MainCamera& camera) {
	this->current_scene->draw(player, ai_vector, camera);
}

//----------------------------Getter----------------------------------

std::shared_ptr<Scene> SceneManager::getCurrentScene() {
	return this->current_scene;
}

std::vector<std::shared_ptr<Scene>>& SceneManager::getScenes() {
	return this->scenes;
}