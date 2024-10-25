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

ParticleSystem* ps;


defs definitions;

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

	createAxis();
	ps = new ParticleSystem();
	// Efecto cascada
	ps->addUniformGenerator(Vector3(0, 0, 0), Vector3(0, 0, 0), 100 , 0.01f, 3.0f, spawn_position_distribution::UNIFORM_SP, 100.0f, 5, Vector4(0.6, 0.6, 1.0, 1));
	//ps->addNormalGenerator(Vector3(100, 0, -100), Vector3(0, 20, 0), 1000, Vector3(10, 0.0001, 10), 1.0f, spawn_position_distribution::UNIFORM_SP, 50);
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
	ps->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	DeregisterRenderItem(sphere);
	DeregisterRenderItem(eje_x);
	DeregisterRenderItem(eje_y);
	DeregisterRenderItem(eje_z);

	delete ps;
	for (auto p : proyectiles) {
		delete p;
	}

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
	case 'H':
		ps->addExplosionGenerator(Vector3(0, 0, 0), Vector3(20, 20, 20), 20, 2, spawn_position_distribution::UNIFORM_SP, 100, 2, Vector4(0, 0, 0, 1));

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