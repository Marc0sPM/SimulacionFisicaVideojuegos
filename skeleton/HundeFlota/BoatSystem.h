#pragma once
#include "../RBSystem.h"
#include "../object_defs.h"
#include <list>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
using namespace physx;
using namespace std;

class BoatSystem
{
private:
	// Lista de botes
	list<Boat* > _boats;
	// Ref al sistema de rigid bodies
	RBSystem*		_sys		= NULL;
	PxScene*		_scene		= NULL;
	PxPhysics*		_physics	= NULL;
	Water*			_water		= NULL;

	//Valores elegidos por el desarrollador de forma arbitraria para el juego

#pragma region Const Parameters
	const int MAX_BOATS = 4; 
	const float SPAWN_HEIGHT = 10.f;
	const Vector3 BOAT_SIZE = { 6, 3, 3 };
	const float MAX_MASS = 2000.f; 
	const float MIN_MASS = 500.f;
	const float MIN_SPEED = 3.f;
	const float MAX_SPEED = 10.f;
#pragma endregion


	//Genera un barco en el plano [x,z] 
	void intialGeneration(); 
	// Al destruirse un barco hay una explosion --> mirar con callbacks 
	void destroyBoat(); 
	
	bool isOverlapping(Vector2 newpos); 

	float calculateRandomMass(); 

	void moveBoat(Boat* boat); 

	void checkLimits(Boat* boat, Vector3 waterPos, Vector3 waterSize); 
public:
	//Constructora del sistema
	// @param rbs sistema de Rigid Body
	// @param surf superficie de generacion para los barcos
	BoatSystem(PxPhysics* ph, PxScene* s, RBSystem* rbs, Water* water) :
		_physics(ph), _scene(s), _sys(rbs),  _water(water) {
		std::srand(static_cast<unsigned int>(std::time(nullptr))); 
	}


	// Mantener este metodo de forma temporal aqui
	void generateBoat(); 

	void init();
	void update(double t); 

	//Devuelve puntero a la lista para evitar copia de memoria
	list<Boat* >*  getBoats() {
		return &_boats;
	}

};

