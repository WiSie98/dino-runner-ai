#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/actor_base.h"


class ActorAI final : public ActorBase {
public:

	ActorAI(bool is_active, int num_inputs, int num_hidden, int num_outputs, Texture texture);

	~ActorAI();

	void update();
	void draw();

	float sigmoidFunction(float x);
	float tanhFunction(float x);
	void fillInputs(int input_pos, float value);

	void setFitness(float fitness);
	void setNearestPlatformEdge(float nearest_platform_edge);
	void setNearestPlatformDistance(float nearest_platform_distance);
	void setNearestPlatformBeneathDistance(float nearest_platform_beneath_distance);

	float getFitness();
	float getNearestPlatformEdge();
	float getNearestPlatformDistance();
	float getNearestPlatformBeneathDistance();
	std::vector<std::vector<Synapse>>& getSynapseVectorHL1();
	std::vector<std::vector<Synapse>>& getSynapseVectorOL();
	std::vector<float>& getSynapseOutHL1();

private:

	void activationFunction();
	void aiMovement();

protected:

	int id;
	float fitness;
	float nearest_platform_edge;
	float nearest_platform_distance;
	float nearest_platform_beneath_distance;

	std::vector<std::vector<Synapse>> synapse_vector_hl1; //Inputs müssen bei der Initialisierung mit Null und die weights mit einem zufälligen float befüllt werden. hl1 -> hidden layer 1, OL -> output layer
	std::vector<std::vector<Synapse>> synapse_vector_ol;
	std::vector<float> synapse_out_hl1;
	std::vector<float> synapse_out_ol;
};