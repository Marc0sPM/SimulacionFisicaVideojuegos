#pragma once
#include "ParticleGenerator.h"
#include <random>
class NormalGenerator : public ParticleGenerator
{
private: 
	//	Velocidad media para distribucion
	Vector3 meanVelocity;
	//	Desviacion tipica para distribucion
	Vector3 devVelocity;

public:
	NormalGenerator(Particle p, float rate, Vector3 meanV, Vector3 devV)
		: ParticleGenerator(p, rate), meanVelocity(meanV), devVelocity(devV) {}

	/**
	*	Genera particulas a partir de una distribucion normal
	*/
	Particle* emit() override;

};

