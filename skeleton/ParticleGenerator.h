#pragma once
#include "Particle.h"

#include <random>
class ParticleSystem;
class ParticleGenerator
{
protected:
	std::mt19937 random_engine;
	float emissionRate; // particulas por segundo
	Vector3 pos;
	Vector3 direction;
    float accumulatedTime = 0.0f;

public:
	ParticleGenerator(Vector3 pos, float rate)
		: pos(pos), emissionRate(rate) {
		std::random_device rd;
		random_engine.seed(rd());
	}

	/**
	*	Metodo virtual para generacion de particulas
	*/
	virtual Particle* emit() = 0;

	void update(double t, ParticleSystem& pS);

	float getEmissionRate() const { return emissionRate; }

};

