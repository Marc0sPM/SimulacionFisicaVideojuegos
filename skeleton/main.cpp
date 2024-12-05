#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Vector3D.h"
#include "Particle.h"
#include "Proyectil.h"
#include "ParticleSystem.h"
#include "TorbellinoGenerator.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include "RBSystem.h"
#include "RWindGenerator.h"
#include "HundeFlota/HF_Scene.h"

#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

//Lista de items
RenderItem* sphere;
RenderItem* eje_x;
RenderItem* eje_y;
RenderItem* eje_z;

std::vector<Proyectil*> proyectiles;

ParticleSystem* ps = nullptr;
ExplosionGenerator* eg = nullptr;

RBSystem* rbs = NULL;

defs definitions;

HF_Scene* hunde_scene;

void printVec(const Vector3& v) {
	std::cout << v.x << ", " << v.y << ", " << v.z << "\n";
 }
void createAxis() {
	//Origen
	PxShape* sShape = CreateShape(PxSphereGeometry(1));
	sphere = new RenderItem(sShape, new PxTransform(PxVec3(0, 0, 0)), Vector4(1, 1, 1, 1));

	// ========================================
	//Eje x
	Vector3D<float> ejeX = Vector3D<float>(10, 0, 0);
	PxTransform* xTr = new PxTransform(ejeX.toPhysix());
	eje_x = new RenderItem(sShape, xTr, Vector4(1, 0, 0, 1));
	// ========================================

	// ========================================
	// Eje y
	Vector3D<float> ejeY = Vector3D<float>(0, 10, 0);
	PxTransform* yTr = new PxTransform(ejeY.x, ejeY.y, ejeY.z);
	eje_y = new RenderItem(sShape, yTr, Vector4(0, 1, 0, 1));
	// ========================================

	// ========================================
	// Eje z
	Vector3D<float> ejeZ = Vector3D<float>(0, 0, 10);
	PxTransform* zTr = new PxTransform(ejeZ.x, ejeZ.y, ejeZ.z);
	eje_z = new RenderItem(sShape, zTr, Vector4(0, 0, 1, 1));
	// ========================================
}

void deregisterAxis() {
	DeregisterRenderItem(sphere);
	DeregisterRenderItem(eje_x);
	DeregisterRenderItem(eje_y);
	DeregisterRenderItem(eje_z);
}
void crearProyectil(proy_type type) {
	auto cam = GetCamera();
	Vector3 camPos = cam->getTransform().p;
	auto dir = cam->getDir();
	
	switch (type)
	{
	case _BULLET:
		proyectiles.push_back(new Proyectil(camPos, dir * definitions.bullet.vel, definitions.bullet.mass, definitions.bullet.fact));
		break;
	case _CANNON:
		proyectiles.push_back(new Proyectil(camPos, dir * definitions.cannon.vel, definitions.cannon.mass, definitions.cannon.fact));
	default:
		break;
	}
}

/**
* Function to set the camera to top view
*/
void setCamTop() {
	auto cam = GetCamera();
	cam->setEye(PxVec3(0.0f, 500.0f, 0.0f));
	cam->setDir(PxVec3(0.0001f, -1.0f, 0.00001f));
}
/**
* Function to set camera to lateral view
*/
void setCamLat() {
	auto cam = GetCamera();
	cam->setEye(PxVec3(1000.0f, 100.0f, 0.0f));
	cam->setDir(PxVec3(-1.0001f, 0.00001f, 0.00001f));
}

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	// createAxis();
	// ps = new ParticleSystem();

	#pragma region PRACTICA 2
	//// Efecto cascada
	//ps->addUniformGenerator(Vector3(0, 0, 0), Vector3(0, -9.8f, 0), 0.1f ,100 , 0.01f, 5.0f, spawn_position_distribution::UNIFORM_SP, 1000.0f, 50, Vector4(0.3, 0.3, 1.0, 1));
	//// Efecto manguera
	//ps->addNormalGenerator(Vector3(30, 0, -30), Vector3(30, 20, -50), 0.1f, 100.0f, Vector3(3, 3, 3), 2.0f, spawn_position_distribution::UNIFORM_SP, 1000.0f, 2, Vector4(1, 0, 0, 1));
	//// Efecto explosion
	//ps->addFireWorkGenerator(Vector3(0, 60, 0), Vector3(0, 50, 0),0.1f ,1.0f, 20, 10.0f, spawn_position_distribution::UNIFORM_SP, 50.0f, 2, Vector4(1, 1, 1, 1));

#pragma endregion

	#pragma region PRACTICA 3
	//Se crean particulas y fuerzas
	//ps->addUniformGenerator(Vector3(0, 0, 0), Vector3(0, 0, 0), 0.5f ,10 , 0.01f, 25.0f, spawn_position_distribution::UNIFORM_SP, 1000.0f, 50, Vector4(1, 0, 0, 1));
	
	
	//auto g2 = ps->addUniformGenerator(Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0f, 100, 0.01f, 25.0f, spawn_position_distribution::UNIFORM_SP, 1000.0f, 50, Vector4(0, 1, 0, 1));
	/*auto g1 = ps->addUniformGenerator(Vector3(0, 0, 0), Vector3(0, 0, 0), 0.01f, 100, 0.01f, 15.0f, spawn_position_distribution::UNIFORM_SP, 1000.0f, 50, Vector4(1, 1, 0, 1));
	eg = new ExplosionGenerator(5000.0f, 100.0f, 0.25f);
	ps->addForce(eg);
	ps->addLink(eg, g1);*/
	
	
	//auto grav1 = ps->addForce(new GravityGenerator(Vector3(0, -15, 0)));
	////ps->addWind(Vector3(0, 50, 0), Vector3(100, 30, 100), Vector3(5, 1, -5), 0.25f);
	//auto t = ps->addForce(new TorbellinoGenerator(Vector3(0, 50, 0), Vector3(300, 5000, 300), 0.25, 2.0f));
	//Se linkean fuerzas y particulas
	//ps->addLink(grav1, g2);
	//ps->addLink(t, g2);

	#pragma endregion

	#pragma region PRACTICA 4
	//pruebaObjecto = new GameObject(Vector3(0, 0, 0), PxBoxGeometry(30.f, 3.f, 30.f), Vector4(0.6f, 0.6f, 1.f, 1.f));
	// ps->generateSpringDemo();
	#pragma endregion

	#pragma region PRACTICA 5
	/*rbs = new RBSystem(gPhysics, gScene);
	auto Objeto2 = rbs->addDynamic({ 0, 10, 0 }, &PxBoxGeometry(4, 4, 4), { 0,0,0,1 }, 0.30); 
	auto Suelo = rbs->addStatic({ 0, -20, 0 }, &PxBoxGeometry(20, 0.01, 20), { 1, 0.8, 0.8, 1 });
	
	auto viento = rbs->addForce(new RWindGenerator({ 10 ,0,1 }, 0.25f));
	rbs->registerObject(viento, Objeto2);*/
#pragma endregion

	#pragma region HundeFlota

	hunde_scene = new HF_Scene(gPhysics, gScene);
	hunde_scene->init();

	#pragma endregion


}
// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	
	gScene->simulate(t);
	gScene->fetchResults(true);

	for (auto p : proyectiles) {
		p->integrate(Particle::integrateType::_EULER_SEMI, t);
	}
	// mParticle->integrate(Particle::integrateType::_EULER,  t);
	if(ps)	ps->update(t);

	if (rbs) rbs->update(t);

	if (hunde_scene) hunde_scene->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	//deregisterAxis();
	if(ps)
		delete ps;

	if (rbs) delete rbs;
	for (auto p : proyectiles) {
		delete p;
	}

	if (hunde_scene) delete hunde_scene;

	_Deref_inout_z_

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case ' ':
	{
		break;
	}
	case 'Q':
		crearProyectil(_BULLET);
		break;
	case 'C': 
		crearProyectil(_CANNON);
		break;
	case 'O':
		setCamTop();
		break;
	case 'P':
		setCamLat();
		break;
	case 'E':
		if(eg != nullptr)
			eg->explode(Vector3(0, 0, 0));
		break;
	case 'J': 
		ps->getSpringDemo()->increaseAnK();
		break;
	case 'K':
		ps->getSpringDemo()->decreaseAnK();
		break;
	case 'L':
		ps->getSpringDemo()->applyArbForce();
		break;
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}