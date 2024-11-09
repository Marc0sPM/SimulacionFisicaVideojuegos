#pragma once
#include "Particle.h"
#include <vector>

enum force_type {
	F_GRAVITY,
	F_WIND,
	F_TORBELLINO,
	F_EXPLOSION,
	F_NONE
};

class ForceGenerator
{
public:
	ForceGenerator(float dur, force_type type = F_NONE, bool alive = true) :  duration(dur), type(type), alive(alive) {}
	~ForceGenerator() {}

	virtual Vector3 calculateForce(Particle* p) = 0;
	virtual void update(double t) = 0;
	bool isAlive() { return alive; }
	force_type getType() const { return type; }
protected:
	float duration;
	bool alive;
	force_type type;
};

