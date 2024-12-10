#pragma once
#include "../RBSystem.h"
#include "../object_defs.h"
#include "BoatSystem.h"
#include "PxPhysicsAPI.h"
#include "../ParticleSystem.h"
#include <cmath>
#include <list>
using namespace physx;

class HF_Scene
{
public:
	HF_Scene(PxPhysics* p, PxScene* scene, Camera* cam) :
		_scene(scene), _physics(p), _camera(cam) {}

	~HF_Scene() {
		delete _sysRB;
		_balls.clear(); 
		_balls_remove.clear();
		delete _boatsys;
	}
	void init();
	void update(double t);
	void cleanup();

	void onKeyPress(unsigned char key);
	void onMouseMove(int x, int y);
	void onMouseClick(int button, int state, int x, int y);
	void onCollision(PxRigidActor* actor1, PxRigidActor* actor2); 

	void spawnFrags(Boat* b);

	std::string getPointsText() const {
		return _text;
	}

private:
	list<Ball*>		_balls;
	vector<Ball*>	_balls_remove; 
	RBSystem*		_sysRB		= NULL;
	ParticleSystem* _psys		= NULL;
	PxScene*		_scene		= NULL; 
	PxPhysics*		_physics	= NULL;
	BoatSystem*		_boatsys	= NULL;
	Camera*			_camera		= NULL;
	Water*			_water		= NULL;

	const Vector3 CAM_POS			= {0.f, 40.f, 165.f};
	const Vector3 CAM_DIR			= {0.00001f, -0.1f,  -1.f};
	const float SHOOT_FORCE			= 220.f;
	const float BALL_MASS			= 5.f;
	const float BALL_RADIUS			= 1.f;
	const float BALL_LIFETIME		= 5.f;
	const Vector4 WATER_COLOR		= { 0.5f, 0.5f ,1.f ,1.f };
	const Vector3 WATER_SIZE		= { 60, 15, 60 };
	const float TIME_TO_SHOOT		= 1.5f;
	const std::string POINTS_TEXT	= "POINTS: ";
	const Vector2 POINTS_POS		= { 0 , 0};
	const int POINTS_BOAT			= 100;
	const Vector3 WIND_VEL			= { 0.f, -500000.f, 0.f }; 

	int _mouseX = 0, _mouseY = 0;
	bool _canShoot = true;
	float _shootTime = TIME_TO_SHOOT;

	int _points = 0;
	std::string _text = POINTS_TEXT + "0";

	physx::PxVec3 getDirectionWithCursor();
		
	void shootBall();

	/**
	*	Elimina la bola si cae por debajo del agua
	*/
	void checkBallLimits();
	
	bool isBallInWater(Vector3 ballPos); 

	void updatePoints(); 
};

