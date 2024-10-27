#pragma once
#include "Particle.h"
#include <vector>
#include <list>
#include <random>
class ParticleSystem;

enum spawn_position_distribution {
	UNIFORM_SP,
	NORMAL_SP
};
enum generator_type {
	UNIFORM, 
	NORMAL,
	FIREWORK
};

class ParticleGenerator
{
protected:
	std::mt19937 random_engine;
	float emissionRate; // particulas por segundo
    float accumulatedTime = 0.0f;
	// Rango en el que se pueden spawnear las particulas
	float spawn_range; 
	// Distribucion de la posicion para spawneo de particulas del generador
	spawn_position_distribution spawn_distribution;
	/**
	*	Define la posicion del generador, la direccion de generacion (vel)
	*/
	Particle model_particle;

	std::list<Particle* > emittedParticles;

	generator_type type;
public:
	

	ParticleGenerator(Particle* p, float rate, float spawnR, spawn_position_distribution sp, generator_type tp)
		: model_particle(*p, true), emissionRate(rate), spawn_range(spawnR), spawn_distribution(sp), type(tp){
		std::random_device rd;
		random_engine.seed(rd());

	}

	/**
	*	Metodo virtual para generacion de particulas
	*/
	virtual void emit() = 0;
	
	/**
	*	Calcula la`posicion de la particula a emitir dependiendo de la distribucion
	*/
	Vector3 calculatePosition();

	void update(double t, ParticleSystem& pS);

	float getEmissionRate() const { return emissionRate; }

	void addParticle(Particle* p) {
		emittedParticles.push_back(p);
	}

};

