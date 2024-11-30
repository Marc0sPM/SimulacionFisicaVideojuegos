#pragma once
#include "RenderUtils.hpp"
using namespace physx;

class GameObject
{
protected:
	RenderItem*		_renderItem		=	NULL;
	PxTransform		_transform;
	Vector4			_color;
	PxShape*		_shape			=	NULL;

	void init_render(PxRigidActor* actor) {
		_renderItem = new RenderItem(_shape, actor, _color);
	}

public:
	GameObject(Vector3 pos, PxGeometry& geometry, Vector4 color)
		: _transform(pos), _color(color), _shape(CreateShape(geometry)) {
	}

	inline void setPosition(const Vector3& newpos) {
		_transform.p = newpos;
	}

	inline Vector3 getPosition() const {
		return _transform.p;
	}

	inline void changeColor(const Vector4& newcolor) {
		_renderItem->color = newcolor;
	}
};

