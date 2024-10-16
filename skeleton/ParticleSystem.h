#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformGenerator.h"
#include "NormalGenerator.h"

enum generators_type {
	UNIFORM,
	NORMAL
};

class ParticleSystem
{
private:
	std::list<Particle* > pList;
	std::vector<ParticleGenerator* > gList; // cambiar a list si se quiere borrar generadores de forma dinamica
	std::vector<Particle*> toErase;
	
	/**
	*	Posicion central de la cual se calcula el rango de existencia
	*	de las particulas del sistema
	*/
	Vector3 center = Vector3(0, 0, 0);
	/**
	*	Radio en el que las particulas existen
	*/
	float ratius;

	// Por defecto, 10 secs
	double particle_lifeTime = 10.0;


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
	*	A�ade una particula a la lista de particulas  
	*	Y establece el iterador correspondiente a esa particula
	*/
	void addParticle(Particle* p);

	/*
	*	A�ade un generador uniforme a la lista de generadores
	*	@param pos Posicion de la cual se generan las particulas
	*	@param direction velocidad media en la cual se emiten las particulas
	*	@param rate Ratio de emision de las particulas
	*	@param range rango de desviacion para calculo de velocidades
	*	@param spawnR rango de generacion de particulas
	*	@param tipo de distribucion para calculo de poscicion
	*/
	void addUniformGenerator(Vector3 pos, Vector3 direction, float rate, float range, float spawnR, spawn_position_distribution sp);

	/**
	*	A�ade un generador de distribucion normal a la lista de generadores
	*	@param pos Posicion de la cual se generan las particulas
	*	@param direction velocidad media en la cual se emiten las particulas
	*	@param rate Ratio de emision de las particulas
	*	@param dev desviacion tipica para calculo de velocidades
	*	@param spawnR rango de generacion de particulas
	*	@param tipo de distribucion para calculo de poscicion
	*/
	void addNormalGenerator(Vector3 pos, Vector3 direction, float rate, Vector3 dev, float spawnR, spawn_position_distribution sp);

	/**
	*	Cambia el tiempo de vida de las particulas que se desea en el sistema
	* 
	*	��� *** Tal vez cambiar posteriormente al generador en especifico o que se genere aleatoriamente
	*			entre un rango especifico *** ???
	*/
	void changeParticleLifeTime(float t) { particle_lifeTime = t; }

	/*
	*	Retorna la el tiempo de vida de las particulas del sistema
	*/
	float getParticleLifeTime() const { return particle_lifeTime; }

	/**
	*	Establece el centro del area de existencia de las particulas
	*/
	void setCenter(Vector3 c) { center = c; }

	/**
	*	Establece el radio del area de existencia de las particulas
	*/
	void setRatius(float r) { ratius = r; }
	 
	/**
	*	@return Radio del area de existencia de las particulas 
	*/
	float getRatius() const { return ratius; } 

	/**
	*	@return Centro del area de existencia de las particulas 
	*/
	Vector3 getCenter() const { return center; } 
};

