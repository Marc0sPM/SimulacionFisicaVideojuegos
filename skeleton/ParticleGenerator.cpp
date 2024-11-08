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
    accumulatedTime += t;
    int particlesToEmit = static_cast<int>(accumulatedTime * emissionRate);
    for (int i = 0; i < particlesToEmit; i++){ 
        emit(); 

        for (auto p : emittedParticles) {
            pS.addParticle(p);
            for (auto fg : linkedForces) {
                pS.addForceToParticle(fg, p);
            }
        }
        emittedParticles.clear();
    }
    accumulatedTime -= particlesToEmit / emissionRate;
}