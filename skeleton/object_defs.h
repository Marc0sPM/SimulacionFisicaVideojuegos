#pragma once
#include "StaticObject.h"
#include "DynamicObject.h"

class Boat : public DynamicObject{
public:
	Boat(PxPhysics* ph, PxScene* sc, Vector3 pos, Vector3 size, Vector4 color, float mass) :
		DynamicObject(ph, sc, pos, &PxBoxGeometry(size), color, mass) {
	}
	~Boat() {
	}

};

class Ball {

};

class Water {

};

class Floor : public StaticObject {
public:
	Floor(PxPhysics* p, PxScene* s, Vector3 pos, Vector2 size, Vector4 color) :
		StaticObject(p, s, pos, &PxBoxGeometry(size.x, 0.01, size.y), color) {
	}
	~Floor() {
	}
};