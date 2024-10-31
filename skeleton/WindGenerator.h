#pragma once
#include "ForceGenerator.h"
class WindGenerator : public ForceGenerator
{
private:
	//centro de perimetro de viento
	Vector3 center;
	//tamaño del perimetro
	Vector3 size;
	//velocidad del viento
	Vector3 windVelocity;
	//coeficiente de rozamiento del aire
	float rozCoef;
public:
	WindGenerator(Vector3 center, Vector3 size, Vector3 wVel, float rozCoef)
		: center(center), size(size), windVelocity(wVel), rozCoef(rozCoef) {
	}

	/**
	*	@param pPos posicion de la particula
	*	@return True si la posicion esta dentro del perimetro de viento, false si esta fuera
	*/
	bool isInside(Vector3 pPos) {
		if (pPos.x < center.x - size.x || pPos.x > center.x + size.x ||
			pPos.y < center.y - size.y || pPos.y > center.y + size.y || 
			pPos.z < center.z - size.z || pPos.z > center.z + size.z) return false;
		return true;

	}
	Vector3 calculateForce(Particle* p) {
		if (isInside(p->getPosition())) {
			return rozCoef * (windVelocity - p->getVelocity());
		}
		else return Vector3(0, 0, 0);
	}
};

