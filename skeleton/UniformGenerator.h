#pragma once
#include "ParticleGenerator.h"
#include <random>

class UniformGenerator : public ParticleGenerator
{
private:
    Vector3 minVelocity;
    Vector3 maxVelocity;

public:
    UniformGenerator(Particle* p, float rate, float range, float spawnRange, spawn_position_distribution sp)
        : ParticleGenerator(p, rate, spawnRange, sp, UNIFORM) 
    {
        Vector3 vel = p->getVelocity();
        Vector3 dev = Vector3(range, range, range);
        minVelocity = vel - dev;
        maxVelocity = vel + dev;
    }

    /**
    *   Genera particulas a partir de una distribucion uniforme
    */
    void  emit() override;
};
