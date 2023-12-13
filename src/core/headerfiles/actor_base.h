#pragma once

#include "header.h"

class ActorBase {
public:

	void setIsDead(bool isDead);
	void setIsActive(bool is_active);
	void setIsStanding(bool is_standing);
	void setTraverseSpeed(float traverse_speed);
	void setJumpSpeed(float jump_speed);
	void setJumpVelocity(float jump_velocity);
	void setCurrentSpeed(float speed_x, float speed_y);
	void setCurrentSpeed(Vector2 current_speed);
	void setCurrentPosition(Vector2 position);
	void setCurrentPosition(float pos_x, float pos_y);
	void setLastPosition(Vector2 position);
	void setLastPosition(float pos_x, float pos_y);
	void setTexture(Texture2D texture);

	bool getIsDead();
	bool getIsActive();
	bool getIsStanding();
	float getTraverseSpeed();
	float getJumpSpeed();
	float getJumpVelocity();
	Vector2 getCurrentSpeed();
	Vector2 getCurrentPosition();
	Vector2 getLastPosition();
	Texture2D getTexture();

	virtual void update() = 0;
	virtual void draw() = 0;

private:

protected:

	bool isDead;
	bool is_active;
	bool is_standing;
	float traverse_speed;
	float jump_speed;
	float jump_velocity;
	Vector2 current_speed;
	Vector2 current_position;
	Vector2 last_position;
	Texture2D texture;

};