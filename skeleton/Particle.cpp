#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel)
{
	vel = Vel;
	pose = physx::PxTransform(Pos);
	renderItem = new RenderItem();
}
