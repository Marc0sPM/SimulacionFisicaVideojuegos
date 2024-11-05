#pragma once
#include "Particle.h"
#include <vector>
class ForceGenerator
{
public:
	ForceGenerator(float dur, bool alive = true) :  duration(dur) {}
	~ForceGenerator() {}

	virtual Vector3 calculateForce(Particle* p) = 0;
	virtual void update(double t) = 0;
	bool isAlive() { return alive; }
protected:
	float duration;
	bool alive;
};

