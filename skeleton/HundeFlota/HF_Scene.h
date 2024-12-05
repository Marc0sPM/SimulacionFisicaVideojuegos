#pragma once
#include "../RBSystem.h"
class HF_Scene
{
public: 
	HF_Scene(PxPhysics* p, PxScene* scene) :
		_scene(scene), _physics(p) {}

	~HF_Scene() {
		delete _sys;
	}
	void init();
	void update(double t);
	void cleanup();

	void onKeyPress(unsigned char key); 

private:
	RBSystem*	_sys		=	NULL;
	PxScene*	_scene		=	NULL;
	PxPhysics*	_physics	=	NULL;

};

