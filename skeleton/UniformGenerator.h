#pragma once
#include "ParticleGenerator.h"
#include <random>

class UniformGenerator : public ParticleGenerator
{
private:
    Vector3 minVelocity;
    Vector3 maxVelocity;

public:
    UniformGenerator(Vector3 pos, float rate, Vector3 minVel, Vector3 maxVel)
        : ParticleGenerator(pos, rate), minVelocity(minVel), maxVelocity(maxVel) {}

    /**
    *   Genera particulas a partir de una distribucion uniforme
    */
    Particle* emit() override;
};
