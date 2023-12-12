#include "headerfiles/actor_base.h"

//----------------------------Setter----------------------------------

void ActorBase::setIsDead(bool isDead) {
	this->isDead = isDead;
}

void ActorBase::setTraverseSpeed(float traverse_speed) {
	this->traverse_speed = traverse_speed;
}

void ActorBase::setJumpSpeed(float jump_speed) {
	this->jump_speed = jump_speed;
}

void ActorBase::setCurrentSpeed(float speed_x, float speed_y) {
	this->current_speed.x = speed_x;
	this->current_speed.y = speed_y;
}

void ActorBase::setCurrentSpeed(Vector2 current_speed) {
	this->current_speed = current_speed;
}

void ActorBase::setCurrentPosition(Vector2 position) {
	this->current_position = position;
}

void ActorBase::setCurrentPosition(float pos_x, float pos_y) {
	this->current_position.x = pos_x;
	this->current_position.y = pos_y;
}

void ActorBase::setLastPosition(Vector2 position) {
	this->last_position = position;
}

void ActorBase::setLastPosition(float pos_x, float pos_y) {
	this->last_position.x = pos_x;
	this->last_position.y = pos_y;
}

void ActorBase::setTexture(Texture2D texture) {
	this->texture = texture;
}

//----------------------------Getter----------------------------------

bool ActorBase::getIsDead() {
	return this->isDead;
}

float ActorBase::getTraverseSpeed() {
	return this->traverse_speed;
}

float ActorBase::getJumpSpeed() {
	return this->jump_speed;
}

Vector2 ActorBase::getCurrentSpeed() {
	return this->current_speed;
}

Vector2 ActorBase::getCurrentPosition() {
	return this->current_position;
}

Vector2 ActorBase::getLastPosition() {
	return this->last_position;
}

Texture2D ActorBase::getTexture() {
	return this->texture;
}