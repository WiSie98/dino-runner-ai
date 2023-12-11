#pragma once

#include "header.h"
#include "camera.h"

class Scene {

public:

	void setSceneType(SceneType scene_type);
	SceneType getSceneType();

	virtual void update(MainCamera& camera) = 0;
	virtual void draw(MainCamera& camera) = 0;

	virtual SceneType setNextScene(bool& exitWindowRequested) = 0;

private:

protected:

	SceneType scene_type;

};