#pragma once
#include "../RBSystem.h"
#include "../object_defs.h"
#include "BoatSystem.h"
#include "PxPhysicsAPI.h"
#include <cmath>
#include <list>
using namespace physx;

class HF_Scene
{
public:
	HF_Scene(PxPhysics* p, PxScene* scene, Camera* cam) :
		_scene(scene), _physics(p), _camera(cam) {}

	~HF_Scene() {
		delete _sys;
	}
	void init();
	void update(double t);
	void cleanup();

	void onKeyPress(unsigned char key);
	void onMouseMove(int x, int y);
	void onMouseClick(int button, int state, int x, int y);
	void onCollision(PxRigidActor* actor1, PxRigidActor* actor2); 

private:
	list<Ball*>		_balls;
	RBSystem*		_sys		= NULL;
	PxScene*		_scene		= NULL; 
	PxPhysics*		_physics	= NULL;
	BoatSystem*		_boatsys	= NULL;
	Camera*			_camera		= NULL;
	Water*			_water		= NULL;

	const Vector3 CAM_POS	= {0.f, 40.f, 150.f};
	const Vector3 CAM_DIR	= {0.00001f, -0.1f,  -1.f};
	const float SHOOT_FORCE = 10000.f; // en N
	const float BALL_MASS	= 5.f;
	const float BALL_RADIUS = 1.f;
	const float BALL_LIFETIME = 5.f;

	int _mouseX = 0, _mouseY = 0;

	physx::PxVec3 getDirectionWithCursor();

	void shootBall();

};

