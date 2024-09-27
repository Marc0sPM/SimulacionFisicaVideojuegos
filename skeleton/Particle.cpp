#include "Particle.h"




Particle::Particle(Vector3 Pos, Vector3 Vel)
{
	vel = Vel;
	pose = physx::PxTransform(Pos);
	PxShape* shape = CreateShape(PxSphereGeometry(1));
	renderItem = new RenderItem(shape, &pose, def_color);
}

void Particle::integrate(double t) {
	pose.p += vel * t;
	vel += acceleration * t;
}
