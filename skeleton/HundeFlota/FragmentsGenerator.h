#pragma once
#include "../ParticleGenerator.h"
class FragmentsGenerator : public ParticleGenerator
{
private:
	int particle_count;
    bool _canEmit = false; 
public:
	FragmentsGenerator(Particle* p, float rate, int count, float spawnR, spawn_position_distribution sp) :
		ParticleGenerator(p, rate, spawnR, sp, FRAGMENTS),
		particle_count(count) {
	}

    ~FragmentsGenerator() override {}

    void emit() override {
        if (_canEmit) {
            Vector3 new_pos = calculatePosition();
            float vel_mod = model_particle.getVelocity().magnitude();
            for (int i = 0; i < particle_count; ++i) {
                Particle* new_particle = new Particle(model_particle);
                new_particle->setPosition(new_pos);
                new_particle->setBoxShape(calulateRandomSize());

                std::uniform_real_distribution<float> speed_distribution(-vel_mod, vel_mod);
                Vector3 random_velocity(
                    speed_distribution(random_engine),
                    speed_distribution(random_engine),
                    speed_distribution(random_engine)
                );
                new_particle->setVelocity(random_velocity.getNormalized() * model_particle.getVelocity().magnitude());

                addParticle(new_particle);
            }
            _canEmit = false;

        }
    }

    void activateFragments( Vector3 pos, Vector4 c) {
        model_particle.setColor(c); 
        model_particle.setPosition(pos);
        _canEmit = true;
    }
    /**
    *   @returns tamaño aleatorio entre dos valores
    */
    float calulateRandomSize() {
        std::uniform_real_distribution<float> size_distribution(MIN_FRAG_SIZE, MAX_FRAG_SIZE);
        float size = size_distribution(random_engine);
        return size;
    }
};

