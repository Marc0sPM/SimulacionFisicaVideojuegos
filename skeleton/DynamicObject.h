#pragma once
#include "GameObject.h"
class DynamicObject : public GameObject
{
private:
	PxRigidDynamic* _rb;
public:
	DynamicObject(PxPhysics* phy, PxScene* scene, Vector3 pos, PxGeometry& geo, Vector4 color, Vector3 vel, Vector3 ang, double mass) :
		GameObject(pos, geo, color)
	{
		_rb = phy->createRigidDynamic(_transform);
		_rb->setLinearVelocity(vel);
		_rb->setAngularVelocity(ang);
		
		_rb->attachShape(*_shape);

		PxRigidBodyExt::updateMassAndInertia(*_rb, mass);
		scene->addActor(*_rb);

		init_render(_rb);	
	}

	inline PxRigidDynamic* getRB() const {
		return _rb;
	}
 };

