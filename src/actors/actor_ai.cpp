#include "headerfiles/actor_ai.h"

ActorAI::ActorAI(bool is_active, int num_inputs, int num_hidden, int num_outputs, Texture texture) {
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
	setFitness(0);

	this->synapse_vector_hl1.resize(num_hidden);
	this->synapse_out_hl1.resize(num_hidden);
	this->synapse_vector_ol.resize(num_outputs);
	this->synapse_out_ol.resize(num_outputs);
	srand(static_cast <unsigned> (time(0)));

	for (int i = 0; i < num_hidden - 1; i++) {
		this->synapse_vector_hl1[i].resize(num_inputs);

		for (int j = 0; j < num_inputs - 1; j++) {
			float random = MINWEIGHT + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAXWEIGHT - MINWEIGHT)));

			Synapse synapse;
			synapse.input = 0;
			synapse.weight = random;

			this->synapse_vector_hl1[i][j] = synapse;
		}
	}

	for (int i = 0; i < num_outputs - 1; i++) {
		this->synapse_vector_ol[i].resize(num_hidden);

		for (int j = 0; j < num_hidden - 1; j++) {
			float random = MINWEIGHT + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAXWEIGHT - MINWEIGHT)));

			Synapse synapse;
			synapse.input = 0;
			synapse.weight = random;

			this->synapse_vector_ol[i][j] = synapse;
		}
	}

}

ActorAI::~ActorAI() {}

void ActorAI::update() {
	if (!getIsDead()) {
		fillInputs();
		activationFunction();
		aiMovement();

		if (this->fitness < (this->current_position.y * -1) + STARTPOSITION.y) {
			this->fitness = ((this->current_position.y * -1) + STARTPOSITION.y);
		}
	}
	if (!getIsStanding()) {
		this->jump_velocity = this->jump_velocity + GRAVITY;
	}
	else {
		this->jump_velocity = 0;
	}

	this->current_position.y += this->jump_velocity + GRAVITY;
}

void ActorAI::draw() {
	if (this->getIsStanding()) {
		DrawTextureRec(this->texture, { 0, 0, 16, 32 }, this->current_position, WHITE);
	}
	else {
		DrawTextureRec(this->texture, { 0, 64, 16, 16 }, { this->current_position.x, this->current_position.y + 16 }, WHITE);
	}
}

void ActorAI::activationFunction() {
	float sum = 0;

	//Calculates the sum of all nodes for the first hidden layer and applys the activation function to the outputs.
	for (int i = 0; i < this->synapse_vector_hl1.size() - 1; i++) {
		for (int j = 0; j < this->synapse_vector_hl1[i].size() - 1; j++) {
			sum += this->synapse_vector_hl1[i][j].input * this->synapse_vector_hl1[i][j].weight; //Der Bias fehlt pro Synapse
		}

		this->synapse_out_hl1[i] = tanhFunction(sum);
		sum = 0;
	}

	//Transfers the calculated output from the nodes of the hidden layer to the input of the nodes from the output layer. 
	for (int i = 0; i < this->synapse_vector_ol.size() - 1; i++) {
		for (int j = 0; j < this->synapse_vector_ol[i].size() - 1; j++) {
			this->synapse_vector_ol[i][j].input = this->synapse_out_hl1[i];
		}
	}

	
	//Calculates the sum of all nodes for the output layer and applys the activation function to the outputs.
	for (int i = 0; i < this->synapse_vector_ol.size() - 1; i++) {
		for (int j = 0; j < this->synapse_vector_ol[i].size() - 1; j++) {
			sum += this->synapse_vector_ol[i][j].input * this->synapse_vector_ol[i][j].weight; //Der Bias fehlt pro Synapse
		}

		this->synapse_out_ol[i] = tanhFunction(sum);
		sum = 0;
	}
}

float ActorAI::sigmoidFunction(float x) {
	float sigmoid = 1 / (1 + exp(-x));
	return sigmoid;
}

float ActorAI::tanhFunction(float x) {
	float tanh = 2 * sigmoidFunction(2 * x) - 1;
	return tanh;
}

void ActorAI::fillInputs() {
	for (int i = 0; i < synapse_vector_hl1.size() - 1; i++) {
		//Input of is_standing
		switch (this->is_standing) {
		case true:
			this->synapse_vector_hl1[i][0].input = 1;
			break;
		case false:
			this->synapse_vector_hl1[i][0].input = -1;
			break;
		}

		//Input of nearest_platform_edge
		if (this->nearest_platform_edge > 192.0f || this->nearest_platform_edge < -192.0f) {
			this->synapse_vector_hl1[i][1].input = -1.0f;
		} else if (this->nearest_platform_edge == 0.0f) {
			this->synapse_vector_hl1[i][1].input = 1.0f;
		} else if (0.0f < this->nearest_platform_edge && this->nearest_platform_edge <= 192.0f) {
			this->synapse_vector_hl1[i][1].input = (this->nearest_platform_edge / 96.0f - 1.0f) * -1.0f;
		} else if (0.0f > this->nearest_platform_edge && this->nearest_platform_edge >= -192.0f) {
			this->synapse_vector_hl1[i][1].input = (this->nearest_platform_edge / -96.0f - 1.0f) * -1.0f;
		}

		//Input of nearest_platform_distance
		if (this->nearest_platform_distance > 256.0f || this->nearest_platform_distance < -256.0f) {
			this->synapse_vector_hl1[i][2].input = -1.0f;
		} else if (this->nearest_platform_distance == 0.0f) {
			this->synapse_vector_hl1[i][2].input = 1.0f;
		} else if (0.0f < this->nearest_platform_distance && this->nearest_platform_distance <= 256.0f) {
			this->synapse_vector_hl1[i][2].input = (this->nearest_platform_distance / 128.0f - 1.0f) * -1.0f;
		} else if (0.0f > this->nearest_platform_distance && this->nearest_platform_distance >= -256.0f) {
			this->synapse_vector_hl1[i][2].input = (this->nearest_platform_distance / -128.0f - 1.0f) * -1.0f;
		}

		//Input of nearest_platform_beneath_distance
		if (this->nearest_platform_beneath_distance > 512.0f) {
			this->synapse_vector_hl1[i][3].input = -1.0f;
		} else if (this->nearest_platform_beneath_distance == 0.0f) {
			this->synapse_vector_hl1[i][3].input = 1.0f;
		} else if (0.0f < this->nearest_platform_beneath_distance && this->nearest_platform_beneath_distance <= 512.0f) {
			this->synapse_vector_hl1[i][3].input = (this->nearest_platform_beneath_distance / 256.0f - 1.0f) * -1.0f;
		} else if (0.0f > this->nearest_platform_beneath_distance && this->nearest_platform_beneath_distance >= -512.0f) {
			this->synapse_vector_hl1[i][3].input = (this->nearest_platform_beneath_distance / -256.0f - 1.0f) * -1.0f;
		}
	}
}

void ActorAI::aiMovement() {
	if (getIsStanding() && synapse_out_ol[0] > 0) {
		this->jump_velocity = this->jump_speed;
		setIsStanding(false);
	}
	if (synapse_out_ol[1] > 0) {
		this->current_position.x = this->current_position.x + this->traverse_speed;
	}
	if (synapse_out_ol[2] > 0) {
		this->current_position.x = this->current_position.x - this->traverse_speed;
	}
}

//----------------------------Setter----------------------------------

void ActorAI::setFitness(float fitness) {
	this->fitness = fitness;
}

void ActorAI::setNearestPlatformEdge(float nearest_platform_edge) {
	this->nearest_platform_edge = nearest_platform_edge;
}

void ActorAI::setNearestPlatformDistance(float nearest_platform_distance) {
	this->nearest_platform_distance = nearest_platform_distance;
}

void ActorAI::setNearestPlatformBeneathDistance(float nearest_platform_beneath_distance) {
	this->nearest_platform_beneath_distance = nearest_platform_beneath_distance;
}

//----------------------------Getter----------------------------------

float ActorAI::getFitness() {
	return this->fitness;
}

float ActorAI::getNearestPlatformEdge() {
	return this->nearest_platform_edge;
}

float ActorAI::getNearestPlatformDistance() {
	return this->nearest_platform_distance;
}

float ActorAI::getNearestPlatformBeneathDistance() {
	return this->nearest_platform_beneath_distance;
}

std::vector<std::vector<Synapse>>& ActorAI::getSynapseVectorHL1() {
	return this->synapse_vector_hl1;
}

std::vector<std::vector<Synapse>>& ActorAI::getSynapseVectorOL() {
	return this->synapse_vector_ol;
}

std::vector<float>& ActorAI::getSynapseOutHL1() {
	return this->synapse_out_hl1;
}