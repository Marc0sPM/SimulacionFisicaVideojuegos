#pragma once
#include "RenderUtils.hpp"
using namespace physx;
class Particle
{
public:
	enum integrateType {
		_EULER,
		_EULER_SEMI,
		_RK,
		_VERLET
	};
	Particle() : 
		vel(Vector3(0,0,0)),
		pose(physx::PxTransform(0,0,0)),
		renderItem(nullptr),
		acceleration(Vector3(0,0,0)) {}

	Particle(Vector3 Pos, Vector3 Vel, Vector3 acc);

	~Particle() {
		DeregisterRenderItem(renderItem);
		renderItem = nullptr;
	}
	//Elige que metodo de integracion usar
	//@param i --> 0:Euler Method 1:
	void integrate(integrateType i, double t);

	void init(Vector3 Pos, Vector3 Vel, Vector3 acc) {
		vel = Vel;
		acceleration = acc;
		pose = physx::PxTransform(Pos);
		PxShape* shape = CreateShape(PxSphereGeometry(1));
		renderItem = new RenderItem(shape, &pose, def_color);
		prevPos = Pos;
	}
protected:

	void integrateEuler(double t);
	void integrateEulerSemi(double t);
	void integrateRK(double t);
	// Mas eficiente a la hora de calcular posicion 
	// Pero es menos eficiente en calcular la velocidad
	void integrateVerlet(double t);

	const double dampingFact = 0.998;
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
	Vector3 acceleration;

	// Posicion previa necesaria para integracion Verlet
	Vector3 prevPos;

	// Color por defecto
	Vector4 def_color = { 0,0,0,1 };
};

