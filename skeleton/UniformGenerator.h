#pragma once
#include "ParticleGenerator.h"
#include <random>

class UniformGenerator : public ParticleGenerator
{
private:
    Vector3 minVelocity;
    Vector3 maxVelocity;

public:
    UniformGenerator(Particle p, float rate, float range)
        : ParticleGenerator(p, rate), minVelocity(p.getVelocity() - Vector3(range, range, range)), maxVelocity(p.getVelocity() + Vector3(range, range, range)) {}

    /**
    *   Genera particulas a partir de una distribucion uniforme
    */
    Particle* emit() override;
};
