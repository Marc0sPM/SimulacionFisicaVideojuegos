#pragma once
#include "ForceGenerator.h"
class WindGenerator : public ForceGenerator
{
private:
	//centro de perimetro de viento
	Vector3 center;
	//tamaño del perimetro
	Vector3 size;
	Vector3 windVelocity;
public:
	WindGenerator(Vector3 center, Vector3 size, Vector3 wVel)
		: center(center), size(size), windVelocity(wVel) {

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
};

