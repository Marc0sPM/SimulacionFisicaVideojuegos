#pragma once
#include "RenderUtils.hpp"
#include <list>
using namespace physx;
const float GRAVITY = -10.0f;
class ParticleSystem;
class Particle
{
public:
	enum integrateType {
		_EULER,
		_EULER_SEMI,
		_RK,
		_VERLET
	};
	/**
	*	Constructora por defecto
	*/
	Particle() : 
		vel(Vector3(0,0,0)),
		pose(physx::PxTransform(0,0,0)),
		renderItem(nullptr),
		acceleration(Vector3(0,0,0)),
		age(0.0)	{
	}
	/**
	*	Constructora de particula simple pensada para proyectil
	*/
	Particle(Vector3 Pos, Vector3 Vel, Vector3 acc = {0,0,0});

	/**
	*	Constructora de particula pensada para un sistema de particulas
	*/
	Particle(Vector3 Pos, Vector3 Vel, float lifetime, Vector3 acc = {0,0,0});

	~Particle() {
		DeregisterRenderItem(renderItem);
		renderItem = nullptr;
	}
	//Elige que metodo de integracion usar
	void integrate(integrateType i, double t);

	/**
	*	Inicializa valores de la particula tal como lo hace la constructora
	*/
	void init(Vector3 Pos, Vector3 Vel, Vector3 acc) {
		vel = Vel;
		acceleration = acc;
		pose = physx::PxTransform(Pos);
		PxShape* shape = CreateShape(PxSphereGeometry(1));
		renderItem = new RenderItem(shape, &pose, def_color);
		prevPos = Pos;
	}

	void update(double t, integrateType type, ParticleSystem& sys);

	/**
	*	Cambia el valor de la aceleracion por el deseado
	*/
	void setAcceleration(const Vector3& a) { acceleration = a; }
	void setIterator(std::list<Particle*>::iterator it) {
		p_it = it;
	}

	std::list<Particle*>::iterator getIterator() const {
		return p_it;
	}
	void setLifeTime(float t) { lifeTime = t; }


protected:

	std::list<Particle*>::iterator p_it;

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

	float age;
	float lifeTime;
};

