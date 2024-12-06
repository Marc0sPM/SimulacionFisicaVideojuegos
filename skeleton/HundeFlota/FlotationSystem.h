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

	/**
	* @returns tamaño real del liquido
	*/
	inline Vector3 getLiquidSize() {
		return _liquid->getBoxSize() * 2;
	}


	inline Vector3 getLiquidPos() {
		return _liquid->getPosition();
	}

private:
	// 'Box' que simula el liquido
	GameObject* _liquid = NULL;

	//Superficie del liquido
	float _liquidLevel;

	//Densidad del liquido
	float _liquidDensity;

	//Gravedad del motor de physics
	Vector3 _gravity;
};

