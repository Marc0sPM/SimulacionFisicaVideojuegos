#pragma once
#include <PxPhysicsAPI.h>
#include "StaticObject.h"
#include "DynamicObject.h"
#include "RigidForceGenerator.h"

#include <list>
#include <unordered_map>
using namespace physx;
typedef std::unordered_map<RigidForceGenerator*, std::list<DynamicObject*> > ForceRegister;

class RBSystem
{
private:
	PxPhysics*	_physics	=	NULL;
	PxScene*	_scene		=	NULL;

	//Lista de objetos estaticos
	std::list<StaticObject* > _statics;
	//Lista de objetos dinamicos
	std::list<DynamicObject* > _dynamics;
	//Lista de generadores de objetos
	
	//Registro de fuerzas 
	ForceRegister _forceRegister;
	//Vector de elementos estaticos a borrar
	std::vector<StaticObject* > _statics_toErase;
	//Vector de elementos dinamicos a borrar
	std::vector<DynamicObject* > _dynamics_toErase;

	inline void applyForces(double t) {
		for (auto& entry : _forceRegister) {
			RigidForceGenerator* g = entry.first;
			for (auto obj : entry.second) {
				g->applyForce(obj, t);
			}
		}
	}

public:
	RBSystem(PxPhysics* phy, PxScene* scene) :
		_physics(phy), _scene(scene) {
	}

	~RBSystem() {
		for (auto s : _statics) {
			_scene->removeActor(*s->getRB());
			delete s;
		}
		_statics.clear();

		for (auto d : _dynamics) {
			_scene->removeActor(*d->getRB());
			delete d;
		}
		_dynamics.clear();

		for (auto& entry : _forceRegister) {
			delete entry.first;
		}
		_forceRegister.clear();

		_statics_toErase.clear();
		_dynamics_toErase.clear();
	}


	inline void update(double t) {

		_statics_toErase.clear(); 
		_dynamics_toErase.clear(); 

		applyForces(t);

		for (auto d : _dynamics) {
			if (d->canDie()) {
				_dynamics_toErase.push_back(d);
			}
			else {
				d->update(t);
			}
		}

		for (auto s : _statics) {
			if (s->canDie()) {
				_statics_toErase.push_back(s);
			}
			else {
				s->update(t);	
			}
		}

		// Eliminacion de objectos
		for (auto s : _statics_toErase) {
			auto it = std::find(_statics.begin(), _statics.end(), s);
			if (it != _statics.end()) {
				_statics.erase(it);
				_scene->removeActor(*s->getRB());
			}
			delete s;
		}
		for (auto d : _dynamics_toErase) {
			auto it = std::find(_dynamics.begin(), _dynamics.end(), d);
			if (it != _dynamics.end()) {
				_dynamics.erase(it);
				_scene->removeActor(*d->getRB());
			}
			delete d;
		}
	}
	/**
	*	Te crea el objecto estatico mediante los parametros de StaticObject y lo añade a la lista de estaticos
	*/
	inline StaticObject* addStatic(Vector3 pos, PxGeometry* geo, Vector4 color) {
		StaticObject* obj = nullptr;
		obj = new StaticObject(_physics, _scene, pos, geo, color);
		_statics.push_back(obj);
		return obj;
	}
	/**
	*	Añade directamente el objecto estatico en la lista
	*/
	inline StaticObject* addStatic(StaticObject* obj) {
		_statics.push_back(obj);
		return obj;
	}
	/**
	*	Te crea el objecto dinamico mediante los parametros de DynamicObject y lo añade a la lista de dinamicos
	*/
	inline DynamicObject* addDynamic(Vector3 pos, PxGeometry* geo, Vector4 color, float mass) {
		DynamicObject* obj = nullptr;
		obj = new DynamicObject(_physics, _scene, pos, geo, color, mass);
		_dynamics.push_back(obj);
		return obj;
	}
	/**
	*	Añade directamente el objecto dinamico en la lista
	*/
	inline DynamicObject*  addDynamic(DynamicObject* obj) {
		_dynamics.push_back(obj);
		return obj;
	}


	inline RigidForceGenerator* addForce(RigidForceGenerator* fg) {
		_forceRegister.insert({ fg, std::list<DynamicObject* >() });
		return fg;
	}

	inline void registerObject(RigidForceGenerator* fg, DynamicObject* obj) {
		auto it = _forceRegister.find(fg);
		if (it != _forceRegister.end()) {
			it->second.push_back(obj);
		}
	}
};

