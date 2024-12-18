#pragma once
#include <vector>
#include <list>
#include <unordered_map>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformGenerator.h"
#include "NormalGenerator.h"
#include "FireWorkGenerator.h"
#include "ExplosionGenerator.h"
#include "SpringDemo.h"
#include "HundeFlota/FragmentsGenerator.h"
#include "HundeFlota/SplashGenerator.h"

class ParticleSystem
{
private:
	std::list<Particle* > pList;
	std::vector<ParticleGenerator* > gList; // cambiar a list si se quiere borrar generadores de forma dinamica
	std::vector<Particle*> toErase;			// vector de particulas a eliminar
	std::unordered_map<ForceGenerator*, std::list<Particle*>> forceRegister; //resgistro de generadores de fuerzas y a que particulas afectan;
	std::vector<ForceGenerator* > fToErase;

	// Generador de fragmentos para el juego
	FragmentsGenerator* _frag	= NULL; 
	SplashGenerator*	_splash = NULL;
	SpringDemo*			spd		= NULL;

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
		for (auto& entry : forceRegister) {
			ForceGenerator* generator = entry.first;  
			std::list<Particle*>& particles = entry.second;  

			particles.clear();

			delete generator;  
		}
		pList.clear();
		toErase.clear();
		gList.clear();

		if (spd) delete spd;
		spd = nullptr;
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
	ParticleGenerator* addUniformGenerator(Vector3 pos, Vector3 direction, float mass,float rate, float range, float spawnR, spawn_position_distribution sp, float rat, float lifetime = 10.0f, Vector4 color = {0,0,0,1});

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
	ParticleGenerator* addNormalGenerator(Vector3 pos, Vector3 direction, float mass, float rate, Vector3 dev, float spawnR, spawn_position_distribution sp, float rat, float lifetime = 10.0f , Vector4 color = {0,0,0,1});
	
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
	ParticleGenerator* addFireWorkGenerator(Vector3 pos, Vector3 direction, float mass, float rate, int particle_count, float spawnR, spawn_position_distribution sp, float rat, float lifetime = 2.0f, Vector4 color = {1,1,1,1}); // poner color aleatoria proximamente
	
	ParticleGenerator* addFragmentsGenerator(Vector3 pos, Vector3 direction, float mass, float rate, int count, float spawnR, spawn_position_distribution sp, float rat, float lifetime = 2.0f);
	ParticleGenerator* addSplashGenerator(Vector3 pos, Vector3 direction, float mass, float rate, int count, float spawnR, spawn_position_distribution sp, float rat, float lifetime = 2.0f,Vector4 color = {1,1,1,1});

	/**
	*	A�ade una explosion al sistema
	*	@param center centro de la explosion
	*	@param k intensidad de la explosion
	*	@param r radio de la explosion
	*	@param tau contante de tiempo de la explosion
	*	@param dur duracion de la explosion
	*/
	ForceGenerator* addExplosionGenerator(float k, float r, float tau);

	/**
	*	acitva la explosion del generador de explosiones
	*	@param center centro de la explosion
	*/
	void addExplosion(Vector3 center);

	/**
	*	Devuelve el primer generador del tipo deseado dentro del registro
	*/
	ForceGenerator* findForce(force_type type);

	/**
	*	Aplica las fuerzas que generan los generadores a la particula
	*	@param p Particula a la que se aplica la fuerza
	*/
	void applyForces(Particle* p);

	/**
	*	Linkea un generador de fuerzas a un generador de particulas de forma que todas las particulas que genere esten resgistradas a ese generador de fuerzas
	*/
	void addLink(ForceGenerator* fg, ParticleGenerator* pg);

	/**
	*	Registra un particula a la lista de correspondiente del generador de fuerza
	*/
	void registerParticle(ForceGenerator* fg, Particle* p);

	/**
	*	A�ade un generador de fuerzas a la lista fList
	*/
	ForceGenerator* addForce(ForceGenerator* fg);

	/** 
	*	Genera una demo para los muelles
	*/
	void generateSpringDemo();

	inline SpringDemo* getSpringDemo() { return spd; }

	inline FragmentsGenerator* getFrag() const {
		return _frag;
	}

	inline SplashGenerator* getSplash() const { 
		return _splash; 
	}


};

