#pragma once
#include "Particle.h"
#include <iostream>


// Tipos de proyectiles
enum proy_type {
	_BULLET,
	_CANNON
};
// Definiciones de distintos proyectiles
struct defs {
	struct Bullet {
		float vel;
		float mass;
		float fact;

		Bullet() : vel(130), mass(0.2), fact(0.5) {}
	} bullet;

	struct Cannon {
		float vel;
		float mass;
		float fact;

		Cannon() : vel(30), mass(10), fact(0.5) {}
	} cannon;
};

class Proyectil : public Particle
{
public :

	Proyectil(const Vector3& pos, const Vector3& vel, float mass, float scaleFactor);

	/**
	*	Operador de salida del proyectil
	*/
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

