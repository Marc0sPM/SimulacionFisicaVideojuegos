#pragma once
#include "ForceGenerator.h"
class ExplosionGenerator : public ForceGenerator
{
public:
	ExplosionGenerator(Vector3 center, float k, float r, float tau)
		: center(center), K(k), R(r), tau(tau), ForceGenerator(tau * 4.0f) {}

	~ExplosionGenerator() {}

	Vector3 calculateForce(Particle* p) {
 		Vector3 distance = p->getPosition() - center;
		float r = distance.magnitude();

		if (r < R) {
			float factor = (K / (r * r)) * physx::PxExp(-duration / tau);
			return distance * factor;
		}
		else {
			return Vector3(0, 0, 0);
		}
	}
	void update(double t) {
		duration -= t;
		if (duration < 0) alive = false;
	}
private:
	//Intensidad de la explosion
	float K;
	//Radio de la explosion
	float R;
	//Constante de tiempo de la explosion
	float tau;
	//Centro de la explosion
	Vector3 center;

};

