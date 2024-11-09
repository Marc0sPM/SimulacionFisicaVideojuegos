#pragma once
#include "ForceGenerator.h"
class ExplosionGenerator : public ForceGenerator
{
public:
	ExplosionGenerator(float k, float r, float tau)
		: center(center), K(k), R(r), tau(tau), ForceGenerator(tau * 4.0f, F_EXPLOSION) {}

	~ExplosionGenerator() {}

	Vector3 calculateForce(Particle* p) {
		if (active) {
 			Vector3 distance = p->getPosition() - center;
			float r = distance.magnitude();

			if (r < R) {
				float factor = (K / (r * r)) * physx::PxExp(-duration / tau);
				return distance * factor;
			}
		}
		return Vector3(0, 0, 0);
	}
	void update(double t) {
		if (active) {
			duration -= t;
			if (duration < 0) active = false;
		}
	}

	/**
	*	activa explosion
	*	@param c coordenada de explosion
	*/
	void explode(Vector3 c) {
		active = true;
		center = c;
	}
private:
	//Intensidad de la explosion
	float K;
	//Radio de la explosion
	float R;
	//Constante de tiempo de la explosion
	float tau;
	//Centro de la explosion
	Vector3 center = Vector3(0, 0, 0);
	//Explosion activa o no
	bool active = false;
};

