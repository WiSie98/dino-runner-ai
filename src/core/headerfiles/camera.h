#pragma once

#include "header.h"

class MainCamera {

public:

	MainCamera(float zoom, float rotation);

	~MainCamera();

	void update();
	void draw();

	void setTarget(Vector2 target);
	void setOffset(Vector2 offset);
	void setOffset(float x, float y);
	void setZoom(float zoom);
	void setRotation(float rotation);

	Camera2D getMainCamera();

private:

	Camera2D mainCamera;

protected:

};