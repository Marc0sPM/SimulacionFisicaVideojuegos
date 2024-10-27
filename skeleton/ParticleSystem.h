#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformGenerator.h"
#include "NormalGenerator.h"
#include "ExplosionGenerator.h"


class ParticleSystem
{
private:
	std::list<Particle* > pList;
	std::vector<ParticleGenerator* > gList; // cambiar a list si se quiere borrar generadores de forma dinamica
	std::vector<Particle*> toErase;			// vector de particulas a eliminar


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
	void killParticle(Particle* p);

	/**
	*	Añade una particula a la lista de particulas  
	*	Y establece el iterador correspondiente a esa particula
	*/
	void addParticle(Particle* p);

	void addParticles(const std::vector<Particle*>& particles);

	/*
	*	Añade un generador uniforme a la lista de generadores
	*	@param pos Posicion de la cual se generan las particulas
	*	@param direction velocidad media en la cual se emiten las particulas
	*	@param rate Ratio de emision de las particulas
	*	@param range rango de desviacion para calculo de velocidades
	*	@param spawnR rango de generacion de particulas
	*	@param sp tipo de distribucion para calculo de poscicion
	*	@param rat radio de existencia de la particula
	*/
	void addUniformGenerator(Vector3 pos, Vector3 direction, float rate, float range, float spawnR, spawn_position_distribution sp, float rat, float lifetime = 10.0f, Vector4 color = {0,0,0,1});

	/**
	*	Añade un generador de distribucion normal a la lista de generadores
	*	@param pos Posicion de la cual se generan las particulas
	*	@param direction velocidad media en la cual se emiten las particulas
	*	@param rate Ratio de emision de las particulas
	*	@param dev desviacion tipica para calculo de velocidades
	*	@param spawnR rango de generacion de particulas
	*	@param sp tipo de distribucion para calculo de poscicion
	*	@param rat radio de existencia de la particula
	*/
	void addNormalGenerator(Vector3 pos, Vector3 direction, float rate, Vector3 dev, float spawnR, spawn_position_distribution sp, float rat, float lifetime = 10.0f , Vector4 color = {0,0,0,1});

	void addExplosionGenerator(Vector3 pos, Vector3 direction, float rate, int particle_count, float spawnR, spawn_position_distribution sp, float rat, float lifetime, Vector4 color);
};

