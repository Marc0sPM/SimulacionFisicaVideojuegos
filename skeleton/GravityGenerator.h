#pragma once
#include "ForceGenerator.h"
class GravityGenerator : public ForceGenerator
{
private:
	Vector3 gravAcc;
public:
	GravityGenerator(Vector3 g = {0, -9.8, 0}, float dur = -1.0f) : gravAcc(g),
		ForceGenerator(dur) {
	}
	Vector3 calculateForce(Particle* p) {
		return p->getMass() * gravAcc;
	}
	void update(double t) {}
};

