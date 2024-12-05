#include "HF_Scene.h"

#include <iostream>
void HF_Scene::init()
{
	_sys = new RBSystem(_physics, _scene);

	// Crear el sistema de flotación
	Water* water = new Water({ 0, 0, 0 }, { 50, 5, 50 }, { 0.0f, 0.0f, 1.0f, 1.0f });
	water->setGravity(_scene->getGravity());
	_sys->addForce(water);


	_boatsys = new BoatSystem(_physics, _scene, _sys, { water->getSurfaceSize().x, water->getSurfaceSize().z }, water);

	_boatsys->generateBoat();
}

void HF_Scene::update(double t)
{
	_sys->update(t);
}

void HF_Scene::cleanup()
{
}

void HF_Scene::onKeyPress(unsigned char key) {
	float massaux = 0.f;
	switch (key)
	{
	case 'g':
		massaux = boat->getRB()->getMass();
		boat->getRB()->setMass(massaux + 5000);
		boat->calculateInertiaTensor(massaux + 5000);
		break;
	default:
		break;
	}
}
