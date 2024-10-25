#include "NormalGenerator.h"

void NormalGenerator::emit()
{
    std::normal_distribution<float> distX(meanVelocity.x, devVelocity.x);
    std::normal_distribution<float> distY(meanVelocity.y, devVelocity.y);
    std::normal_distribution<float> distZ(meanVelocity.z, devVelocity.z);

    Vector3 randomVelocity(distX(random_engine), distY(random_engine), distZ(random_engine));
    Particle* p = new Particle(model_particle);

    p->setVelocity(randomVelocity);
    p->setPosition(calculatePosition());

    addParticle(p);
}
