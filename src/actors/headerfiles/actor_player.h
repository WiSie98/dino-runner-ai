#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/actor_base.h"

class ActorPlayer final : public ActorBase {
public:
	
	ActorPlayer(float position_x, float position_y, Texture2D texture);

	~ActorPlayer() {};

	void update() override;
	void draw() override;

private:

	void playerMovement();

protected:

};