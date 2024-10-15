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

    Particle* emit() override {
        // Generar una velocidad aleatoria usando una distribución uniforme
        std::uniform_real_distribution<float> distX(minVelocity.x, maxVelocity.x);
        std::uniform_real_distribution<float> distY(minVelocity.y, maxVelocity.y);
        std::uniform_real_distribution<float> distZ(minVelocity.z, maxVelocity.z);

        Vector3 randomVelocity(distX(random_engine), distY(random_engine), distZ(random_engine));

        // Crear una nueva partícula en la posición de la fuente con la velocidad generada
        Particle* newParticle = new Particle(pos, randomVelocity, Vector3(0,GRAVITY,0));

        return newParticle;
    }
};
