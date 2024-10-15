#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformGenerator.h"

using PG = ParticleGenerator;



enum generators_type {
	UNIFORM,
	NORMAL
};

class ParticleSystem
{
private:
	std::list<Particle* > pList;
	std::vector<PG* > gList;
	std::vector<Particle*> toErase;

	double particle_lifeTime = 5.0;

public:
	ParticleSystem() {}

	~ParticleSystem() {
		for (auto p : pList) {
			delete p;
			p = nullptr;
		}
		for (auto g : gList) {
			delete g;
			g = nullptr;
		}

		pList.clear();
		gList.clear();

	}

	/**
	*	Actualiza todos los elementos del sistema
	*	@param t Tiempo de actualizacion
	*/
	void update(double t);

	/**
	*	Elimina una particula de la lista de particulas
	*	@param p Particula que se quiere eliminar
	*/
	void killParticle(Particle* p) {
		if(p != nullptr && p->getIterator() != pList.end())
			toErase.push_back(p);
	}

	/**
	*	Añade una particula a la lista de particulas a partir de su posicion, velocidad y aceleracion 
	*	? -> mirar si hacer esto o pasar solo la particula y crearla en el generador
	*/
	void addParticle(Particle* p) {
		pList.push_back(p);
		p->setIterator(--pList.end());
		
	}

	void addGenerator(Vector3 pos, float rate, generators_type type);

	void changeParticleLifeTime(float t) { particle_lifeTime = t; }

	float getParticleLifeTime() const { return particle_lifeTime; }
};

