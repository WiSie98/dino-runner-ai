#pragma once

#include "../../core/headerfiles/header.h"
#include "../../core/headerfiles/actor_base.h"


class ActorAI final : public ActorBase {
public:

	ActorAI(float start_position_x, float start_position_y, int num_inputs, int num_hidden, int num_outputs);

	~ActorAI();

	void update();
	void draw();

	void activationFunction();
	float sigmoidFunction(float x);
	float tanhFunction(float x);

	void setIsStanding(bool is_standing);
	void setFitness(float fitness);
	void setNearestPlatformEdge(float nearest_platform_edge);
	void setNearestPlatformDistance(float nearest_platform_distance);
	void setNearestPlatformBeneathDistance(float nearest_platform_beneath_distance);

	bool getIsStanding();
	float getFitness();
	float getNearestPlatformEdge();
	float getNearestPlatformDistance();
	float getNearestPlatformBeneathDistance();
	std::vector<std::vector<Synapse>>& getSynapseVectorHL1();
	std::vector<float>& getSynapseOutHL1();

private:

	

protected:

	bool is_standing;
	float fitness;
	float nearest_platform_edge;
	float nearest_platform_distance;
	float nearest_platform_beneath_distance;

	std::vector<std::vector<Synapse>> synapse_vector_hl1; //Inputs müssen bei der Initialisierung mit Null und die weights mit einem zufälligen float befült werden. hl1 -> hidden layer 1, OL -> output layer
	std::vector<std::vector<Synapse>> synapse_vector_ol;
	std::vector<float> synapse_out_hl1;
	std::vector<float> synapse_out_ol;
};