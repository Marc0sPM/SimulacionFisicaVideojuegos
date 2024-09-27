#include "Particle.h"
#include <math.h>



Particle::Particle(Vector3 Pos, Vector3 Vel)
{
	vel = Vel;
	pose = physx::PxTransform(Pos);
	PxShape* shape = CreateShape(PxSphereGeometry(1));
	renderItem = new RenderItem(shape, &pose, def_color);
}

void Particle::integrate(double t) {
	// Velocidad constante
	pose.p += vel * t;
	//Velocidad con aceleracion
	vel += acceleration * t;
	//Damping para correcion de velocidad
	vel = vel * pow(dampingFact, t);
}
