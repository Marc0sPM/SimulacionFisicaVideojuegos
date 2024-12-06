	#pragma once
	#include "StaticObject.h"
	#include "DynamicObject.h"
	#include "HundeFlota/FlotationSystem.h"
	#include <cstdlib>
	#include <ctime>

enum move_dir {
	RIGHT = 0, 
	LEFT,
	STILL
};
	
// Objecto de los barcos
class Boat : public DynamicObject{
public:
	Boat(PxPhysics* ph, PxScene* sc, Vector3 pos, Vector3 size, Vector4 color, float mass, float ini_vel = 5.f) :
		DynamicObject(ph, sc, pos, &PxBoxGeometry(size), color, mass) {
		_rb->setLinearDamping(0.5);
		speed = ini_vel;
		if (speed > 0.f) {
			direction = move_dir::RIGHT; 
		}
		else if (speed < 0.f) { 
			direction = move_dir::LEFT; 
		}
		else {
			direction = move_dir::STILL;
		}
	}
	~Boat() override {
	}
	//Velocidad de movimiento del bote
	float speed;
	move_dir direction;
};

// Objecto de bola que es el proyectil
class Ball : public DynamicObject {
public: 
	Ball(PxPhysics* ph, PxScene* sc, Vector3 pos, float r, Vector4 color, float mass) :
		DynamicObject(ph, sc, pos, &PxSphereGeometry(r), color, mass) {
	}
};

// Generador de fuerza de flotacion que simula agua
class Water : public FlotationSystem {
public:
	Water(Vector3 pos, Vector3 size, Vector4 color) :
		FlotationSystem(pos, size, 1000.f, color) {
	}
};

// Objecto de suelo, que no se utiliza de momento
class Floor : public StaticObject {
public:
	Floor(PxPhysics* p, PxScene* s, Vector3 pos, Vector2 size, Vector4 color) :
		StaticObject(p, s, pos, &PxBoxGeometry(size.x, 0.01, size.y), color) {
	}
	~Floor() {
	}
};


inline Vector4 GenerateRandomColor() {

	// Generar componentes rojo y verde aleatorios en el rango [0, 1]
	float r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
	float g = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
	float b = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

	return { r, g, b , 1.f};
}


