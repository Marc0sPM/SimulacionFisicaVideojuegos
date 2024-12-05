#pragma once
#include "../RigidForceGenerator.h"
class FlotationSystem : public RigidForceGenerator	{

public: 
	FlotationSystem( Vector3 pos, Vector3 liquidSize, float liquidDensity, Vector4 liquidColor); 
	/*
	* Calcula la fuerza de rotacion dando por hecho que los objectos que flotan son cubos o prismas rectangulares
	*/
	void applyForce(DynamicObject* obj, double t) override;

	void setGravity(Vector3 grav) {
		_gravity = grav;
	}

	inline Vector3 getSurfaceSize() {
		return _liquid->getBoxSize() * 2;
	}
private:
	// 'Box' que simula el liquido
	GameObject* _liquid = NULL;

	//Superficie del liquido
	float _liquidLevel;

	//Densidad del liquido
	float _liquidDensity;

	Vector3 _gravity; 

	float _dragCoef = 0.1;

	bool _firstUpdate = true;
};

