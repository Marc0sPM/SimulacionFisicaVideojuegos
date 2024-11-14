#pragma once
#include "ForceGenerator.h"
class GravityGenerator : public ForceGenerator
{
private:
	Vector3 gravAcc;
public:
	GravityGenerator(Vector3 g = {0, -9.8, 0}) : gravAcc(g),
		ForceGenerator(-1, F_GRAVITY) {
	}
	Vector3 calculateForce(Particle* p) {
		return p->getMass() * gravAcc;
	}
	void update(double t) {}
};

