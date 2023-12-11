#include "headerfiles/main_scene.h"

MainScene::MainScene() {
	setSceneType(MAIN_SCENE);
}

MainScene::~MainScene() {}

void MainScene::update(MainCamera& camera) {}

void MainScene::draw(MainCamera& camera) {
	DrawText("Hello, world!", 10, 10, 30, LIGHTGRAY);
}

SceneType MainScene::setNextScene(bool& exitWindowRequested) {

	if (IsKeyPressed(KEY_BACKSPACE)) {
		return START_SCENE;
	}
	else if (IsKeyPressed(KEY_ESCAPE)) {
		exitWindowRequested = true;
	}

	return MAIN_SCENE;
}