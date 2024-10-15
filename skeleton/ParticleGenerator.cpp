#include "ParticleGenerator.h"
#include "ParticleSystem.h"

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