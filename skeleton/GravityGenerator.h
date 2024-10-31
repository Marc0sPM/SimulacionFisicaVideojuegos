#pragma once
#include "ForceGenerator.h"
class GravityGenerator : public ForceGenerator
{
private:
	Vector3 gravAcc;
public:
	GravityGenerator(Vector3 g = {0, -9.8, 0}) : gravAcc(g),
		ForceGenerator() {
	}
	Vector3 calculateForce(Particle* p) {
		return p->getMass() * gravAcc;
	}
	
};

