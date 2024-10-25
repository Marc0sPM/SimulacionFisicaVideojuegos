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
	Particle();
	/**
	*	Constructora de particula simple pensada para proyectil
	*/
	Particle(Vector3 Pos, Vector3 Vel, Vector3 acc = {0,0,0});

	/**
	*	Constructora de particula pensada para un sistema de particulas
	*/
	Particle(Vector3 Pos, Vector3 Vel, float lifetime, Vector3 acc = {0,0,0});

	/**
	*	Constructora a partir de otra particula para evitar la copia
	*/
	Particle(Particle const& p);
	/**
	*	Destructora, desregistra el renderItem que representa la particula
	*/
	virtual ~Particle() {
		DeregisterRenderItem(renderItem);
		delete renderItem;
		renderItem = nullptr;
	}

	/**
	*	Ejecuta el metodo de integracion que se pasa
	*/
	void integrate(integrateType i, double t);

	/**
	*	Inicializa valores de la particula tal como lo hace la constructora
	*/
	void init(Vector3 Pos, Vector3 Vel, Vector3 acc = Vector3(0, GRAVITY,0));

	/**
	*	Llama al metodo de integracion, compruba el tiempo de vida
	*/
	void update(double t, integrateType type, ParticleSystem& sys);

	/**
	*	Cambia el valor de la aceleracion por el deseado
	*/
	void setAcceleration(const Vector3& a) { acceleration = a; }
	/**
	*	Establece el iterador de la lista de particulas correspondiente
	*/
	void setIterator(std::list<Particle*>::iterator it) {
		p_it = it;
	}
	/**
	*	Devuelve el iterador de la particula
	*/
	std::list<Particle*>::iterator getIterator() const {
		return p_it;
	}
	/**
	*	Establece el limite de tiempo que vive la particula
	*/
	void setLifeTime(float t) { lifeTime = t; }

	/**
	*	Compruba si la particula esta dentro del radio deseado
	*	tomando v como el centro
	*/
	bool isOnRatio();

	/**
	*	Cambia la posicion de la particula
	*/
	void setPosition(Vector3 p) {
		pose.p = p;
	}
	
	/**
	*	Cambia la velocidad de
	*/
	void setVelocity(Vector3 v) {
		vel = v;
	}

	Particle& operator=(const Particle& p) {
		init(p.pose.p, p.vel, p.acceleration);
		age = p.age;
		return *this;
	}

	Vector3 getVelocity() const {
		return vel;
	}

	Vector3 getPosition() const {
		return pose.p;
	}

	void setRatius(float r) {
		rat = r;
	}

	float getRatius() const {
		return rat;
	}

	void setColor(Vector4 c) {
		color = c;
	}

	float getLifeTime() const {
		return lifeTime;
	}
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

	// Posicion central del generador
	Vector3 center;

	//Radio de "vida" del generador
	float rat;

	// Color por defecto
	Vector4 color;
	

	float age;
	float lifeTime;
};

