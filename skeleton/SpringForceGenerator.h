#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator : public ForceGenerator
{
public :
	SpringForceGenerator(float k, float resting_length, Particle* other) 
		: _k(k), _resting_length(resting_length), _other(other) {}

	void update(double t) override {}

	virtual Vector3 calculateForce(Particle* p) override {
		// Se calcula la posicion relativa de la particula respecto a la otra particula
		Vector3 rel_pos = _other->getPosition() - p->getPosition();

		//Se normaliza esa longitud y se saca la elongacion ( variacion de x ) 
		const float length = rel_pos.normalize();
		const float delta_x = length - _resting_length;

		// Ley de Hooke
		return  rel_pos * delta_x * _k;
	}

	inline void setK(double k) { _k = k; }  
	inline float& getK() { return _k; }

	virtual ~SpringForceGenerator() {}

protected:
	float _k;				// Coeficiente elastico
	float _resting_length;	// Longitud en reposo
	Particle* _other;		// Particula a la que esta anclada
};

