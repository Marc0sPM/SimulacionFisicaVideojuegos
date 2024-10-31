#pragma once
#include "Particle.h"
#include <vector>
class ForceGenerator
{
public:
	ForceGenerator() {}
	~ForceGenerator() {}

	virtual Vector3 calculateForce(Particle* p) = 0;
};

