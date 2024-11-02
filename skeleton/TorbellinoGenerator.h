#pragma once
#include "WindGenerator.h"
class TorbellinoGenerator : public WindGenerator
{
private:
	float intensity;

	void calculateVelocity(Vector3 pPos) override ;

public:
	TorbellinoGenerator(Vector3 center, Vector3 size, float rozCoef, float intensity)
		: intensity(intensity), WindGenerator(center, size, Vector3(0,0,0), rozCoef) {
	}
};

