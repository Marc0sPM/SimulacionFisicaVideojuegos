#pragma once
#include "Particle.h"
#include <vector>
class ForceGenerator
{
public:
	ForceGenerator() {}
	~ForceGenerator() {}

	virtual Vector3 calculateAcc(Particle* p) = 0;
};

