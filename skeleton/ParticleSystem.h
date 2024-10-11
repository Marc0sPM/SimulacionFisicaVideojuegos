#pragma once
#include <vector>
#include "Particle.h"
#include "ParticleGenerator.h"

using PG = ParticleGenerator;

class ParticleSystem
{
private:
	std::vector<Particle* > pList;
	std::vector<PG* > gList;

	/**
	*	Actualiza las particulas del sistema
	*/
	void updateParticles(float t);

	/**
	*	Actualiza los generadores de las particulas
	*/
	void updateGenerators(float t);

public:
	ParticleSystem() {}

	/**
	*	Actualiza todos los elementos del sistema
	*	@param t Tiempo de actualizacion
	*/
	void update(float t);

	/**
	*	Elimina una particula de la lista de particulas
	*	@param p Particula que se quiere eliminar
	*/
	void killParticle(Particle* p);

	/**
	*	Añade una particula a la lista de particulas a partir de su posicion, velocidad y aceleracion 
	*	? -> mirar si hacer esto o pasar solo la particula y crearla en el generador
	*/
	void addParticle(const Vector3& pos, const Vector3& vel, const Vector3& acc);

	void addGenerator();

	
};

