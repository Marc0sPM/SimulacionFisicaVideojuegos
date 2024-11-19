#pragma once
#include "RenderUtils.hpp"
using namespace physx;

class GameObject
{
private:
	RenderItem* _renderItem;
	PxTransform _transform;
	Vector4 _color;
public:
	GameObject(Vector3 pos, PxGeometry& geometry, Vector4 color)
		: _transform(pos), _color(color) {
		_renderItem = new RenderItem(CreateShape(geometry), &_transform, _color);
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

