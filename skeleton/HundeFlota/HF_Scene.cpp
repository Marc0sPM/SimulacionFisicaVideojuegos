#include "HF_Scene.h"
#include "../object_defs.h"

void HF_Scene::init()
{
	_sys = new RBSystem(_physics, _scene);
	
	_sys->addStatic(new Floor(_physics, _scene, Vector3(0,0,0), Vector2(20, 20), Vector4(0.8, 0.8, 0.8, 1.0)));
	_sys->addDynamic(new Boat(_physics, _scene, Vector3(0, 20, 0), Vector3(3, 3, 3), Vector4(1, 0, 1, 1), 5.f));
	_sys->addDynamic(new Boat(_physics, _scene, Vector3(0, 40, 0), Vector3(3, 3, 3), Vector4(1, 1, 0, 1), 5.f));
}

void HF_Scene::update(double t)
{
}

void HF_Scene::cleanup()
{
}

void HF_Scene::onKeyPress(unsigned char key) {
	switch (key)
	{
	default:
		break;
	}
}
