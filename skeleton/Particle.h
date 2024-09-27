#pragma once
#include "RenderUtils.hpp"
using namespace physx;
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	~Particle() {
		DeregisterRenderItem(renderItem);
		renderItem = nullptr;
	}

	void integrate(double t);
private:
	const double dampingFact = 0.998;
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
	Vector3 acceleration = { 0,2,0 };

	//Default color
	Vector4 def_color = { 0,0,0,1 };
};

