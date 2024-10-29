#pragma once
#include "ForceGenerator.h"
class GravityGenerator : public ForceGenerator
{
private:
	Vector3 gravForce;
public:
	GravityGenerator(Vector3 grav) : gravForce(grav),
		ForceGenerator() {
	}

	Vector3 calculateAcc(Particle* p) override {
		return gravForce / p->getMass();
	}
};

