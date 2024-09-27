#pragma once
#include "RenderUtils.hpp"
using namespace physx;
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	~Particle() {
		delete renderItem;
		renderItem = nullptr;
	}

	void integrate(double t);
private:
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;

	//Default color
	Vector4 def_color = { 0,0,0,1 };
};

