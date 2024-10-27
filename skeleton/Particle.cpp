#include "Particle.h"
#include <math.h>
#include <iostream>
#include "ParticleSystem.h"

Particle::Particle() {
	vel = Vector3(0, 0, 0);
	pose = physx::PxTransform(0, 0, 0);
	renderItem = nullptr; 
	acceleration = Vector3(0, 0, 0);
	age = 0.0; 
	
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 acc)
{
	init(Pos, Vel, acc);
	age = 0;
}

Particle::Particle(Particle const& p, bool isModel) {
	color = p.color;
	init(p.getPosition(), p.vel, p.acceleration, isModel);
	center = p.getPosition();
	rat = p.rat;
	lifeTime = p.lifeTime;
}

void Particle::init(Vector3 Pos, Vector3 Vel, Vector3 acc, bool isModel) {
	vel = Vel;
	acceleration = acc;
	pose = physx::PxTransform(Pos);
	PxShape* shape = CreateShape(PxSphereGeometry(1));
	if (!isModel) {
		renderItem = new RenderItem(shape, &pose, color);
	}
	prevPos = Pos;
}

void Particle::integrate(integrateType i, double t) {
	switch (i)
	{
	case _EULER:
		integrateEuler(t);
		break;
	case _EULER_SEMI:
		integrateEulerSemi(t);
		break;
	case _RK:
		integrateRK(t);
		break;
	case _VERLET:
		integrateVerlet(t);
	default:
		break;
	}
}

void Particle::update(double t, integrateType type, ParticleSystem& sys)
{
	age += t;
	integrate(type, t);
	if (age > lifeTime || !isOnRatio()) sys.killParticle(this);
}

bool Particle::isOnRatio()
{
	if (rat < 0) return true; // -1 en caso de que no se quiera evaluar con el radio
	return (pose.p - center).magnitude() < rat;
}

void Particle::integrateEuler(double t) {
	// Actualizamos velocidad
	vel += acceleration * t;


	// Damping 
	vel = vel * pow(dampingFact, t);
	// Actualizamos posicion
	pose.p += vel * t;

	/*  
	*	No valdria tambien con hacer vel *= dampingFact ? ? ? 
	*/
}

void Particle::integrateEulerSemi(double t) {
	// Primero se actualiza la posicion
	pose.p += vel * t;
	// Luego la velocidad
	vel += acceleration * t;
	// Damping
	vel = vel * pow(dampingFact, t);
}

void Particle::integrateRK(double t)
{
	// Vel y pos inicial
	const Vector3 initialPos = pose.p;
	const Vector3 initialVel = vel;

	// k1
	const Vector3 k1Vel = acceleration * t;
	const Vector3 k1Pos = vel * t;

	// k2
	const Vector3 k2Vel = acceleration * t;
	const Vector3 k2Pos = (initialVel + k1Vel * 0.5) * t;

	// k3
	const Vector3 k3Vel = acceleration * t;
	const Vector3 k3Pos = (initialVel + k2Vel * 0.5) * t;

	// k4
	const Vector3 k4Vel = acceleration * t;
	const Vector3 k4Pos = (initialVel + k3Vel) * t;

	// Combinacion de cada fase 
	pose.p = initialPos + (k1Pos + 2.0 * k2Pos + 2.0 * k3Pos + k4Pos) / 6.0;
	vel = initialVel + (k1Vel + 2.0 * k2Vel + 2.0 * k3Vel + k4Vel) / 6.0;

	// Damping
	vel *= pow(dampingFact, t);
}

void Particle::integrateVerlet(double t)
{
	const Vector3 currPos = pose.p;

	pose.p = 2 * currPos - prevPos + acceleration * (t * t);

	// Calculo de velocidad - no es necesario 
	
	/*vel = (pose.p - currPos) / t;
	
	vel *=  dampingFact;*/
	
	prevPos = currPos;
	 
}
