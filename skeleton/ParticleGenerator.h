#pragma once
#include "Particle.h"
#include <random>

class ParticleGenerator
{
protected:
	std::mt19937 random_engine;
	float emissionRate;
	Vector3 pos;

public:
	ParticleGenerator(Vector3 pos, float rate)
		: pos(pos), emissionRate(rate) {
		std::random_device rd;
		random_engine.seed(rd());
	}

	virtual Particle* emit() = 0;

	float getEmissionRate() const { return emissionRate; }
};

