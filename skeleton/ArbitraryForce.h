#pragma once
#include "ForceGenerator.h"
class ArbitraryForce : public ForceGenerator
{
public:
	ArbitraryForce(Vector3 force, )
		: _force(force) {}

	void update(double t) override {}

	Vector3 calculateForce() {
		return _force;
	}
private:
	Vector3 _force;
};

