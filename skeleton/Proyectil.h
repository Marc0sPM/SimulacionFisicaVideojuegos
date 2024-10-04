#pragma once
#include "Particle.h"
#include <iostream>

class Proyectil : public Particle
{
public :
	Proyectil(const Vector3& pos, const Vector3& vel, float mass, float scaleFactor);

	friend std::ostream& operator<<(std::ostream& os, const Proyectil& proyectil) {
		os << "Masa real: " << proyectil.mass_r
			<< ", Masa simulada: " << proyectil.mass_s
			<< ", Gravedad simulada: " << proyectil.grav_s
			<< ", Velocidad real: "
			<< proyectil.vel_r.x << " "
			<< proyectil.vel_r.y << " "
			<< proyectil.vel_r.z << " "
			<< ", Velocidad simulada: "
			<< proyectil.vel.x << " "
			<< proyectil.vel.y << " "
			<< proyectil.vel.z << " \n";
		return os;
	}

private: 
	// Masa real del proyectil
	float mass_r;
	// Masa simulada del proyectil
	float mass_s;
	// Velocidad real del proyectil
	Vector3 vel_r;
	// Velocidad simulada del proyectil
	Vector3 vel_s;
	// Valor de la aceleracion de la gravedad real
	const float grav_r = 9.8;
	// Valor de la gravedad simulada
	float grav_s;
	// Factor de escalado
	float scale_fact;

	/**
	*	Ajusta los parametros de simulacion en base a un factor de simulacion para la velocidad
	*/
	void adjustParameters();
};

