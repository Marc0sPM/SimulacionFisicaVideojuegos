#pragma once
#include "RenderUtils.hpp"
using namespace physx;

enum rb_type {
	STATIC, 
	DYNAMIC, 
	NONE
};

class GameObject
{
protected:
	RenderItem*		_renderItem		=	NULL;
	PxTransform		_transform;
	Vector4			_color;
	PxShape*		_shape			=	NULL;

	rb_type _rb_type;
	bool _active = true;
	float _life_time = -1; // Tiempo de vida (-1 es infinito)

	/**
	*	Inicializa el render item del objeto
	*/
	inline void init_render(PxRigidActor* actor) {
		_renderItem = new RenderItem(_shape, actor, _color);
	}

public:
	GameObject(Vector3 pos, PxGeometry* geometry, Vector4 color, rb_type type )
		: _transform(pos), _color(color), _shape(CreateShape(*geometry)), _rb_type(type){
	}
	~GameObject() {
		if (_renderItem) {
			DeregisterRenderItem(_renderItem);
			_renderItem = nullptr;
		}
		_shape = nullptr;
	}
	/**
	*	Actualiza el tiempo de vida del objeto 
	*/
	inline void update(double t) {
		if (_life_time > -1) {
			_life_time -= t;
			if (_life_time < 0) _active = false;
		}
		
	}
	inline bool canDie() {
		return !_active;
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

	inline void setLifeTime(float t) {
		_life_time = t;
	}

	inline void changeShape(PxGeometry* newGeo) {
		_renderItem->shape = CreateShape(*newGeo);
	}
	inline rb_type getRBType() const {
		return _rb_type;
	}
};

