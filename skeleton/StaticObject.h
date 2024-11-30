#pragma once
#include "GameObject.h"
class StaticObject : public GameObject
{
private:
	PxRigidStatic* _rb;
public: 
	StaticObject(PxPhysics* phy, PxScene* scene, Vector3 pos, PxGeometry& geo, Vector4 color) : 
		GameObject(pos, geo, color)
	{
		_rb = phy->createRigidStatic(_transform);
		_rb->attachShape(*_shape);
		scene->addActor(*_rb);

		init_render(_rb);
	}

	inline PxRigidStatic* getRB() const {
		return _rb;
	}
};

