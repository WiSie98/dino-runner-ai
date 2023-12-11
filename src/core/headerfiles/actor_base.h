#pragma once

#include "header.h"

class ActorBase {
public:

	void setIsDead(bool isDead);
	void setTraverseSpeed(float traverse_speed);
	void setCurrentPosition(Vector2 position);
	void setCurrentPosition(float pos_x, float pos_y);
	void setLastPosition(Vector2 position);
	void setLastPosition(float pos_x, float pos_y);
	void setTexture(Texture2D texture);

	bool getIsDead();
	float getTraverseSpeed();
	Vector2 getCurrentPosition();
	Vector2 getLastPosition();
	Texture2D getTexture();

	virtual void update() = 0;
	virtual void draw() = 0;

private:

protected:

	bool isDead;
	float traverse_speed;
	Vector2 current_position;
	Vector2 last_position;
	Texture2D texture;

};