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

const Vector3 BOAT_SIZE = { 6, 3, 3 };
const int MAX_BOATS = 4; 

class HF_Scene;
class BoatSystem
{
private:

#pragma region Const Parameters
	const float MAX_MASS = 2000.f; 
	const float MIN_MASS = 500.f;
	const float MIN_SPEED = 3.f;
	const float MAX_SPEED = 10.f;
	const double SPAWN_TIME = 5.0; // Tiempo de spawneo, en segundos 
#pragma endregion

	// Lista de botes
	list<Boat* > _boats;
	//Lista de botes a eliminar
	vector<Boat* > _remove_boats;
	// Ref al sistema de rigid bodies
	RBSystem*		_sys		= NULL;
	PxScene*		_scene		= NULL;
	PxPhysics*		_physics	= NULL;
	Water*			_water		= NULL;
	HF_Scene*		_hf_scene	= NULL;	

	double _counter = SPAWN_TIME;

	float _spawnHeight; 

	
	bool isOverlapping(Vector2 newpos); 

	float calculateRandomMass(); 

	void moveBoat(Boat* boat); 

	void checkLimits(Boat* boat, Vector3 waterPos, Vector3 waterSize); 
public:
	//Constructora del sistema
	// @param rbs sistema de Rigid Body
	// @param surf superficie de generacion para los barcos
	BoatSystem(HF_Scene* hf, PxPhysics* ph, PxScene* s, RBSystem* rbs, Water* water) :
		_hf_scene(hf), _physics(ph), _scene(s), _sys(rbs),  _water(water), _spawnHeight(_water->getLiquidPos().y + (_water->getLiquidSize().y / 2)  + BOAT_SIZE.y + 2) {
		std::srand(static_cast<unsigned int>(std::time(nullptr))); 
	}
	// Mantener este metodo de forma temporal aqui
	void generateBoat(); 

	void init() {
		for (int i = 0; i < MAX_BOATS; ++i) {
			generateBoat();
		}
	}
	void update(double t); 

	
	void removeBoat(Boat* boat);

	//Devuelve puntero a la lista para evitar copia de memoria
	list<Boat* >*  getBoats() {
		return &_boats;
	}

};

