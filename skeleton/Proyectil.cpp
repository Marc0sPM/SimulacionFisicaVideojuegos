#include "Proyectil.h"

Proyectil::Proyectil(const Vector3& pos, const Vector3& vel, float mass, float scaleFactor) : Particle(){
	mass_r = mass;
	vel_r = vel;
	scale_fact = scaleFactor;

	adjustParameters();

	Particle(pos, vel_s, Vector3(0, -grav_s, 0));
}

void Proyectil::adjustParameters()
{
	// Modulos de las velocidades
	vel_s = vel_r * scale_fact;

	float mod_r = vel_r.magnitude();
	float mod_s = vel_s.magnitude();

	// masa simulada
	mass_s = mass_r * pow(mod_r, 2) / pow(mod_s, 2);

	// gravedad simulada
	grav_s = grav_r * pow(mod_s, 2) / pow(mod_r, 2);
}
