#pragma once
#include "Particle.h"

#include <random>
class ParticleSystem;
class ParticleGenerator
{
protected:
	std::mt19937 random_engine;
	float emissionRate; // particulas por segundo
    float accumulatedTime = 0.0f;

	/**
	*	Define la posicion del generador, la direccion de generacion (vel)
	*/
	Particle model_particle;

public:
	
	ParticleGenerator(Particle p, float rate)
		: model_particle(p), emissionRate(rate) {
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

