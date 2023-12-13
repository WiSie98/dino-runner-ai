#include "headerfiles/actor_player.h"

ActorPlayer::ActorPlayer(bool is_active, Texture2D texture) {
	setIsDead(false);
	setIsActive(is_active);
	setIsStanding(true);
	setTraverseSpeed(TRAVERSESPEED);
	setJumpSpeed(JUMPSPEED);
	setJumpVelocity(0);
	setCurrentSpeed(0, 0);
	setCurrentPosition(STARTPOSITION);
	setLastPosition(STARTPOSITION);
	setTexture(texture);
}

void ActorPlayer::update() {
	if (!getIsStanding()) {
		this->jump_velocity = this->jump_velocity + GRAVITY;
	} else {
		this->jump_velocity = 0;
	}

	if (!getIsDead()) {
		playerMovement();
	}
	this->current_position.y += this->jump_velocity + GRAVITY;
}

void ActorPlayer::draw() {
	if (this->getIsStanding()) {
		DrawTextureRec(this->texture, { 0, 0, 16, 32 }, this->current_position, WHITE);
	} else {
		DrawTextureRec(this->texture, { 0, 64, 16, 16 }, { this->current_position.x, this->current_position.y + 16 }, WHITE);
	}
}

void ActorPlayer::playerMovement() {
	if (getIsStanding() && IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
		this->jump_velocity = this->jump_speed;
		setIsStanding(false);
	}
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
		this->current_position.x = this->current_position.x + this->traverse_speed;
	}
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
		this->current_position.x = this->current_position.x - this->traverse_speed;
	}
}

//----------------------------Setter----------------------------------



//----------------------------Getter----------------------------------
