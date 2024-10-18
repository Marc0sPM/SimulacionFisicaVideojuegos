#include "UniformGenerator.h"

Particle* UniformGenerator::emit()
{
    std::uniform_real_distribution<float> distX(minVelocity.x, maxVelocity.x);
    std::uniform_real_distribution<float> distY(minVelocity.y, maxVelocity.y);
    std::uniform_real_distribution<float> distZ(minVelocity.z, maxVelocity.z);
    
    Vector3 randomVelocity(distX(random_engine), distY(random_engine), distZ(random_engine));

    Particle* newParticle = new Particle(model_particle);

    newParticle->setVelocity(randomVelocity);
    newParticle->setPosition(calculatePosition());

    return newParticle;
}
