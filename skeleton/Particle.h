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
	Particle(const Vector3& Pos,const Vector3& Vel, const Vector3& acc);
	~Particle() {
		DeregisterRenderItem(renderItem);
		renderItem = nullptr;
	}
	//Elige que metodo de integracion usar
	//@param i --> 0:Euler Method 1:
	void integrate(integrateType i, double t);
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
	Vector3 acceleration = { 0,3,0 };

	// Posicion previa necesaria para integracion Verlet
	Vector3 prevPos;

	// Color por defecto
	Vector4 def_color = { 0,0,0,1 };
};

