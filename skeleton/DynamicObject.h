#pragma once
#include "GameObject.h"

class DynamicObject : public GameObject	{

protected:
	PxRigidDynamic* _rb;

public:
	DynamicObject(PxPhysics* phy, PxScene* scene, Vector3 pos, PxGeometry* geo, Vector4 color, double mass);
	virtual ~DynamicObject() override {
		_rb->release();
	}
	inline PxRigidDynamic* getRB() const {
		return _rb;
	}
	
	/**
	*	@returns el vector de inercia de forma manual en base a la forma del objeto dinamico
	*/
	Vector3 calculateInertiaTensor(float mass);

	inline void setLinearVelocity(Vector3 vel) {
		_rb->setLinearVelocity(vel);
	}
	inline Vector3 getLinearVelocity() {
		return _rb->getLinearVelocity();
	}
	inline void setAngularVelocity(Vector3 ang) {
		_rb->setAngularVelocity(ang);
	}
	inline void addForce(Vector3 f) {
		_rb->addForce(f);
	}
	inline void addTorque(Vector3 t) {
		_rb->addTorque(t);
	}

	inline virtual void update(double t) override {}
 };

