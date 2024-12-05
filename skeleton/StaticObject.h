#pragma once
#include "GameObject.h"
class StaticObject : public GameObject
{
private:
	PxRigidStatic* _rb = nullptr;
public: 
	StaticObject(PxPhysics* phy, PxScene* scene, Vector3 pos, PxGeometry* geo, Vector4 color) : 
		GameObject(pos, geo, color, rb_type::STATIC)
	{
		_rb = phy->createRigidStatic(_transform);
		_rb->attachShape(*_shape);
		scene->addActor(*_rb);

		init_render_RB(_rb);
	}
	~StaticObject() {

	}
	inline PxRigidStatic* getRB(){
		return _rb;
	}
};

