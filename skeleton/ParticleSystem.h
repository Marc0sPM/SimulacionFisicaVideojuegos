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
	*	Añade una particula a la lista de particulas  
	*	Y establece el iterador correspondiente a esa particula
	*/
	void addParticle(Particle* p);

	/*
	*	Añade un generador a la lista de generadores
	*	@param pos Posicion de la cual se generan las particulas
	*	@param rate Ratio de emision de las particulas
	*	@param type Tipo de generacion que se desea
	*	
	*/
	void addGenerator(Vector3 pos, float rate, generators_type type);

	/**
	*	Cambia el tiempo de vida de las particulas que se desea en el sistema
	* 
	*	¿¿¿ *** Tal vez cambiar posteriormente al generador en especifico o que se genere aleatoriamente
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

