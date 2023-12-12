#pragma once

#include "header.h"

class ActorBase {
public:

	void setIsDead(bool isDead);
	void setTraverseSpeed(float traverse_speed);
	void setJumpSpeed(float jump_speed);
	void setCurrentSpeed(float speed_x, float speed_y);
	void setCurrentSpeed(Vector2 current_speed);
	void setCurrentPosition(Vector2 position);
	void setCurrentPosition(float pos_x, float pos_y);
	void setLastPosition(Vector2 position);
	void setLastPosition(float pos_x, float pos_y);
	void setTexture(Texture2D texture);

	bool getIsDead();
	float getTraverseSpeed();
	float getJumpSpeed();
	Vector2 getCurrentSpeed();
	Vector2 getCurrentPosition();
	Vector2 getLastPosition();
	Texture2D getTexture();

	virtual void update() = 0;
	virtual void draw() = 0;

private:

protected:

	bool isDead;
	float traverse_speed;
	float jump_speed;
	Vector2 current_speed;
	Vector2 current_position;
	Vector2 last_position;
	Texture2D texture;

};