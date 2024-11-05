#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformGenerator.h"
#include "NormalGenerator.h"
#include "FireWorkGenerator.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"
#include "TorbellinoGenerator.h"
#include "ExplosionGenerator.h"

class ParticleSystem
{
private:
	std::list<Particle* > pList;
	std::vector<ParticleGenerator* > gList; // cambiar a list si se quiere borrar generadores de forma dinamica
	std::vector<Particle*> toErase;			// vector de particulas a eliminar
	std::list<ForceGenerator* > fList;
	std::vector<ForceGenerator* > fToErase;	// vector de generadores de fuerzas a eliminar

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
		for (auto f : fList) {
			delete f;
			f = nullptr;
		}

		pList.clear();
		gList.clear();
		fList.clear();
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
	*	@param sp tipo de distribucion para calculo de poscicion
	*	@param rat radio de existencia de la particula
	*/
	void addUniformGenerator(Vector3 pos, Vector3 direction, float mass,float rate, float range, float spawnR, spawn_position_distribution sp, float rat, float lifetime = 10.0f, Vector4 color = {0,0,0,1});

	/**
	*	A�ade un generador de distribucion normal a la lista de generadores
	*	@param pos Posicion de la cual se generan las particulas
	*	@param direction velocidad media en la cual se emiten las particulas
	*	@param rate Ratio de emision de las particulas
	*	@param dev desviacion tipica para calculo de velocidades
	*	@param spawnR rango de generacion de particulas
	*	@param sp tipo de distribucion para calculo de poscicion
	*	@param rat radio de existencia de la particula
	*/
	void addNormalGenerator(Vector3 pos, Vector3 direction, float mass, float rate, Vector3 dev, float spawnR, spawn_position_distribution sp, float rat, float lifetime = 10.0f , Vector4 color = {0,0,0,1});
	
	/**
	*	A�ade un generador con efecto de fuegos artificiales
	*	@param pos Posicion de la cual se generan las particulas
	*	@param direction velocidad media en la cual se emiten las particulas
	*	@param rate Ratio de emision de las particulas
	*	@param particle_count numero de particulas generadas en cada explosion
	*	@param spawnR rango de generacion de particulas
	*	@param sp tipo de distribucion para calculo de poscicion
	*	@param rat radio de existencia de la particula
	*/
	void addFireWorkGenerator(Vector3 pos, Vector3 direction, float mass, float rate, int particle_count, float spawnR, spawn_position_distribution sp, float rat, float lifetime = 2.0f, Vector4 color = {1,1,1,1}); // poner color aleatoria proximamente
	
	/**
	*	A�ade un generador de gravedad al sistema
	*	@param grav vector de gravedad
	*/
	void addGravity(Vector3 grav = {0, -9.8, 0});
	
	/**
	*	A�ade un generador de viento al sistema
	*	@param center Posicion central del perimetro donde hay viento
	*	@param size Dimensiones del perimetro
	*	@param windVel velocidad del viento
	*	@param rCoef coeficiente de rozamiento del aire
	*/
	void addWind(Vector3 center, Vector3 size, Vector3 windVel, float rCoef);

	/**
	*	A�ade un generador de torbellino al sistema
	*	@param center Posicion central del torbellino
	*	@param size Dimensiones del torbelino
	*	@param rCoef coeficiente de rozamiento del aire
	*	@param intensity intensidad de la fuerza del torbellino
	*/
	void addTorbellino(Vector3 center, Vector3 size, float rozCoef, float intensity);

	/**
	*	A�ade una explosion al sistema
	*	@param center centro de la explosion
	*	@param k intensidad de la explosion
	*	@param r radio de la explosion
	*	@param tau contante de tiempo de la explosion
	*	@param dur duracion de la explosion
	*/
	void addExplosion(Vector3 center, float k, float r, float tau);

	/**
	*	Aplica las fuerzas que generan los generadores a la particula
	*	@param p Particula a la que se aplica la fuerza
	*	@param t deltaTime
	*/
	void applyForces(Particle* p, double t);

};

