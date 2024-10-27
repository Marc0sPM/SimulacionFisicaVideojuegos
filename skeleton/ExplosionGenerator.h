#pragma once
#include "ParticleGenerator.h"
#include <vector>

class ExplosionGenerator : public ParticleGenerator {
private:
    int particle_count; 

public:
    
    ExplosionGenerator(Particle* p, float rate, int count, float spawnR, spawn_position_distribution sp)
        : ParticleGenerator(p, rate, spawnR, sp, FIREWORK), particle_count(count) {}

    
    void emit() override {
        Vector3 new_pos = calculatePosition();
        for (int i = 0; i < particle_count; ++i) {
            Particle* new_particle = new Particle(model_particle);
            new_particle->setPosition(new_pos);

            std::uniform_real_distribution<float> speed_distribution(-1.0f, 1.0f);
            Vector3 random_velocity(
                speed_distribution(random_engine),
                speed_distribution(random_engine),
                speed_distribution(random_engine)
            );
            new_particle->setVelocity(random_velocity.getNormalized() * model_particle.getVelocity().magnitude());

            addParticle(new_particle);
        }

        
    }
};
