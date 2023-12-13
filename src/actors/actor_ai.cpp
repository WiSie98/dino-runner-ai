#include "headerfiles/actor_ai.h"

ActorAI::ActorAI(float start_position_x, float start_position_y, int num_inputs, int num_hidden, int num_outputs) {
	this->synapse_vector_hl1.resize(num_hidden);
	this->synapse_out_hl1.resize(num_hidden);
	this->synapse_vector_ol.resize(num_outputs);
	this->synapse_out_ol.resize(num_outputs);
	srand(static_cast <unsigned> (time(0)));

	for (int i = 0; i < num_hidden - 1; i++) {
		this->synapse_vector_hl1[i].resize(num_inputs);

		for (int j = 0; j < num_inputs - 1; j++) {
			float random = -2.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f - -2.0f)));

			Synapse synapse;
			synapse.input = 0;
			synapse.weight = random;

			this->synapse_vector_hl1[i][j] = synapse;
		}
	}

	for (int i = 0; i < num_outputs - 1; i++) {
		this->synapse_vector_ol[i].resize(num_hidden);

		for (int j = 0; j < num_hidden - 1; j++) {
			float random = -2.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f - -2.0f)));

			Synapse synapse;
			synapse.input = 0;
			synapse.weight = random;

			this->synapse_vector_ol[i][j] = synapse;
		}
	}

}

ActorAI::~ActorAI() {}

void ActorAI::update() {
	//Davor müssen noch die Inputs für die ersten Synapsen berechnet und übergeben werden.
	activationFunction();
}

void ActorAI::draw() {

}

void ActorAI::activationFunction() {
	float sum = 0;

	//Calculates the summ of all nodes for the first hidden layer and applys the activation function to the outputs.
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


	//Calculates the summ of all nodes for the output layer and applys the activation function to the outputs.
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

std::vector<float>& ActorAI::getSynapseOutHL1() {
	return this->synapse_out_hl1;
}