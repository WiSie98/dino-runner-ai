#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/actor_base.h"

class ActorPlayer final : public ActorBase {
public:
	
	ActorPlayer(bool is_active, Texture2D texture);

	~ActorPlayer() {};

	void update() override;
	void draw() override;

private:

	void playerMovement();

protected:

};