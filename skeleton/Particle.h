#pragma once
#include "RenderUtils.hpp"
#include <list>
#include <iostream>
using namespace physx;
const float GRAVITY = -10.0f;
class ParticleSystem;

enum shape {
	SPHERE, 
	BOX
};
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
	Particle(Vector3 Pos, Vector3 Vel, Vector3 acc = {0,0,0}, Vector4 color = {0.8, 0.8, 0.8, 1.0}, shape sh = SPHERE);

	/**
	*	Constructora de particula pensada para un sistema de particulas
	*/
	Particle(Vector3 Pos, Vector3 Vel, float lifetime, Vector3 acc = {0,0,0});

	/**
	* Constructora para muelles y eso 
	*/
	Particle(Vector3 Pos, Vector3 size, Vector4 color = { 1,1,1,1 }, shape sh = SPHERE);
	/**
	*	Constructora a partir de otra particula para evitar la copia
	*/
	Particle(Particle const& p, bool isModel = false);
	/**
	*	Destructora, desregistra el renderItem que representa la particula
	*/
	virtual ~Particle() {
		// std::cout << "Destruye particula: " << this << "\n";
		if (renderItem != nullptr) {
			//std::cout << "BORRA PARTICULA\n";
 			DeregisterRenderItem(renderItem);
			//delete renderItem;
			renderItem = nullptr;
		}
	}

	/**
	*	Ejecuta el metodo de integracion que se pasa
	*/
	void integrate(integrateType i, double t);

	/**
	*	Inicializa valores de la particula tal como lo hace la constructora
	*/
	void init(Vector3 Pos, Vector3 Vel, Vector3 acc = Vector3(0, 0, 0), shape sh = SPHERE, bool isModel = false);

	/**
	*	Llama al metodo de integracion, compruba el tiempo de vida
	*/

	//Cambiar posteriormente para que se le pase una fuerza y que 

	void update(double t, integrateType type, ParticleSystem& sys);

	/**
	*	@return true si la particula se le a acabado su tiempo de vida o si esta fuera del radio del generador, false en caso contrario
	*/
	bool canDie();

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
	void setModelP() {
		DeregisterRenderItem(renderItem);
	}
	void setMass(float m) {
		mass = m;
	}
	float getMass() const {
		return mass; 
	}
	void setForce(Vector3 f) {
		force = f;
	}
	Vector3 getForce() const {
		return force;
	}
	void setCenter(Vector3 c) { center = c; }
	inline Vector3 getSize() const {
		return size;
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
	RenderItem* renderItem = nullptr;
	Vector3 acceleration;
	Vector3 force = { 0,0,0 };

	// Posicion previa necesaria para integracion Verlet
	Vector3 prevPos;

	// Posicion central del generador
	Vector3 center = Vector3(0, 0, 0);
	Vector3 size = Vector3(0, 0, 0);

	//Radio de "vida" del generador
	float rat;

	// Color por defecto
	Vector4 color;
	
	float mass;
	float lifeTime;
};

