#pragma once
#include "GravityGenerator.h"
#include "Particle.h"
#include "ArbitraryForce.h"
#include "AnchoredSpringFG.h"
#include "FlotationForceGenerator.h"
class ParticleSystem;
struct slink {
	AnchoredSpringFG* s_an = nullptr;
	Particle* s_p1 = nullptr;
	Particle* s_p2 = nullptr;
	Particle* s_p3 = nullptr;
	Particle* s_p4 = nullptr;
	SpringForceGenerator* s_sp1_2 = nullptr;
	SpringForceGenerator* s_sp2_1 = nullptr;
	SpringForceGenerator* s_sp2_3 = nullptr;
	SpringForceGenerator* s_sp3_2 = nullptr;
	SpringForceGenerator* s_sp3_4 = nullptr;
	SpringForceGenerator* s_sp4_3 = nullptr;
	float k1, k2, k3, an_k; //constantes de los muelles
	float l1, l2, l3, an_l; //longitudes en reposo de los muelles
	float life = 10000;
};
class SpringDemo
{ 
private:
	ParticleSystem* _ps = nullptr;
	GravityGenerator* g1 = nullptr;
	ArbitraryForce* ar1 = nullptr;
	slink _slink;

	// Ejercicio2 --------------------------
	Particle* p1 = nullptr;
	Particle* p2 = nullptr;

	SpringForceGenerator* sp1 = nullptr;
	SpringForceGenerator* sp2 = nullptr;
	// -------------------------------------
	// 
	// Ejercicio 1 -------------------------
	Particle* p3 = nullptr;

	AnchoredSpringFG* an1 = nullptr;
	// -------------------------------------

	// Ejercicio 3 -------------------------
	FlotationForceGenerator* ffg;
	Particle* f_p1;
public:
	SpringDemo(ParticleSystem* ps);
	~SpringDemo() {}
	/**
	* Inicializa la demostracion de muelles
	*/
	void init();
	/*
	* Aumenta la K de an1 - AnchoredSpringFG
	*/
	inline void increaseAnK() {
		if(an1) an1->getK() += 0.5;
	}
	/**
	* Disminuye la K de an1 - AnchoredSpringFG
	*/
	inline void decreaseAnK() {
		if(an1) an1->getK() -= 0.5;
	}
	/**
	* Activa la fuerza que genera ArbitraryForce
	*/
	inline void applyArbForce() {
		if(ar1) ar1->apply();
	}
	/**
	* Crea un slink
	*/
	void createSlink();
	/**
	* Crea una particula atada a unn sitio fijo mediante un muelle
	*/
	void anchoredSpring();
	void particleSpring();
	void flotationSystem();
};

