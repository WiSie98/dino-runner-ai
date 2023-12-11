#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/scene.h"

class MainScene final : public Scene {
public:

	MainScene();

	~MainScene();

	void update(MainCamera& camera) override;
	void draw(MainCamera& camera) override;
	SceneType setNextScene(bool& exitWindowRequested) override;

private:

};