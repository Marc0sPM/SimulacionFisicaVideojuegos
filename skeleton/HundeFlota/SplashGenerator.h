#pragma once
#include "../ParticleGenerator.h"
class SplashGenerator : public ParticleGenerator
{
private:
	int particle_count; 
	bool _canEmit = false;
public: 
	SplashGenerator(Particle* p, float rate, int count, float spawnR, spawn_position_distribution sp) :
		ParticleGenerator(p, rate, spawnR, sp, SPLASH),
		particle_count(count) {
	}
    void emit() override {
        if (_canEmit) {
            Vector3 new_pos = calculatePosition();
            Vector3 base_velocity = model_particle.getVelocity();
            float vel_mod = base_velocity.magnitude();

            // Reducir la dispersión en X y Z para concentrar partículas hacia el centro
            std::normal_distribution<float> sdx(0, vel_mod * 0.1f); // Menor dispersión en X
            std::normal_distribution<float> sdz(0, vel_mod * 0.1f); // Menor dispersión en Z

            // Variación en la fuerza del eje Y
            std::uniform_real_distribution<float> y_variation_factor(0.5f, 1.0f); // Algunas partículas serán más bajas

            for (int i = 0; i < particle_count; ++i) {
                Particle* new_particle = new Particle(model_particle);
                new_particle->setPosition(new_pos);

                // Generar posición inicial aleatoria en X y Z con mayor probabilidad de estar cerca del centro
                float random_x = sdx(random_engine);
                float random_z = sdz(random_engine);

                // Modificar la probabilidad de distancia usando una función cuadrática
                float radial_distance = sqrt(random_x * random_x + random_z * random_z);

                // Escalar la velocidad en Y según la proximidad al centro
                float max_height = vel_mod * 1.5f;
                float height_scale = std::fmax(0.0f, max_height * (1.0f - radial_distance / vel_mod));

                // Aplicar un factor adicional para concentrar partículas hacia el centro
                float central_focus_factor = exp(-radial_distance / (vel_mod * 0.5f)); // Refuerza partículas en el centro
                random_x *= central_focus_factor;
                random_z *= central_focus_factor;

                // Ajustar la altura con un factor aleatorio
                height_scale *= y_variation_factor(random_engine); // Variación en la fuerza de Y

                // Crear velocidad ajustada
                Vector3 random_velocity(
                    random_x,
                    height_scale,
                    random_z
                );

                new_particle->setVelocity(random_velocity);
                addParticle(new_particle);
            }
            _canEmit = false;
        }
    }


    void spawnSplash(Vector3 pos) {
        model_particle.setPosition(pos);
        _canEmit = true;
    }

};

