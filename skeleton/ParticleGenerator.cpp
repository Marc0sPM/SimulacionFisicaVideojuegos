#include "ParticleGenerator.h"
#include "ParticleSystem.h"

Vector3 ParticleGenerator::calculatePosition()
{
    Vector3 modPos = model_particle.getPosition();
    Vector3 endPos;
    
    if (spawn_distribution == UNIFORM_SP) {

        std::uniform_real_distribution<float> distX(modPos.x - spawn_range, modPos.x + spawn_range);
        std::uniform_real_distribution<float> distY(modPos.y - spawn_range, modPos.y + spawn_range);
        std::uniform_real_distribution<float> distZ(modPos.z - spawn_range, modPos.z + spawn_range);
        endPos = Vector3(distX(random_engine), distY(random_engine), distZ(random_engine));
    }
    else if(spawn_distribution == NORMAL_SP) {

        Vector3 dev = { spawn_range, spawn_range, spawn_range };
        std::normal_distribution<float> distX(modPos.x , spawn_range);
        std::normal_distribution<float> distY(modPos.y , spawn_range);
        std::normal_distribution<float> distZ(modPos.z , spawn_range);
        endPos = Vector3(distX(random_engine), distY(random_engine), distZ(random_engine));
    }
    return endPos;
}

void ParticleGenerator::update(double t, ParticleSystem& pS ) {
    // Acumula el tiempo
    accumulatedTime += t;

    // Particulas a emitir
    int particlesToEmit = static_cast<int>(accumulatedTime * emissionRate);

    for (int i = 0; i < particlesToEmit; ++i) {
        Particle* newParticle = emit();
        if (newParticle) {
            pS.addParticle(newParticle);
            newParticle->setLifeTime(pS.getParticleLifeTime());
        }
    }

    // Restar el tiempo emitido
    accumulatedTime -= particlesToEmit / emissionRate;
}