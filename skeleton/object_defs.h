	#pragma once
	#include "StaticObject.h"
	#include "DynamicObject.h"
	#include "HundeFlota/FlotationSystem.h"
	#include <cstdlib>
	#include <ctime>

	class Boat : public DynamicObject{
	public:
		Boat(PxPhysics* ph, PxScene* sc, Vector3 pos, Vector3 size, Vector4 color, float mass) :
			DynamicObject(ph, sc, pos, &PxBoxGeometry(size), color, mass) {
			_rb->setLinearDamping(0.5);
		}
		~Boat() {
		}

	};

	class Ball {

	};

	class Water : public FlotationSystem {
	public:
		Water(Vector3 pos, Vector3 size, Vector4 color) :
			FlotationSystem(pos, size, 1000.f, color) {
		}
	};

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
		float b = 0.f;

		// Para que no haya color negro puro
		if (r == 0.0f && g == 0.0f) {
			r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
			g = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
		}

		return { r, g, b , 1.f};
	}


