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
ExplosionGenerator* eg = nullptr;
SpringForceGenerator* sp1;
SpringForceGenerator* sp2;
AnchoredSpringFG* ac1;

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

void generateSpringDemo()
{
	// Ejercicio 2
	Particle* p1 = new Particle(Vector3(-10.0, 10.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0, 0, 0), Vector4(0.5, 0.0, 1.0, 1.0));
	p1->setLifeTime(100);
	p1->setRatius(1000);
	p1->setMass(2.0f);

	Particle* p2 = new Particle(Vector3(10.0, 10.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0, 0, 0), Vector4(1.0, 0.5, 0.0, 1.0));
	p2->setRatius(1000);
	p2->setLifeTime(100);
	p2->setMass(2.0f);

	ps->addParticle(p1);
	ps->addParticle(p2);

	sp1 = new SpringForceGenerator(0.98, 10, p2);
	sp2 = new SpringForceGenerator(0.98, 10, p1);

	ps->addForce(sp1);
	ps->addForce(sp2);

	ps->registerParticle(sp1, p1);
	ps->registerParticle(sp2, p2);

	//Ejercicio 1
	Particle* p3 = new Particle(Vector3(0.0, 30.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0, 0, 0), Vector4(1.0, 0.5, 0.0, 1.0));
	p3->setLifeTime(1000);
	p3->setRatius(10000);
	p3->setMass(2.0);

	ps->addParticle(p3);

	ac1 = new AnchoredSpringFG(1, 20, Vector3(0, 30, 0));
	ac1->setAnchorLife(1000);
	ps->addForce(ac1);

	ps->registerParticle(ac1, p3);

	GravityGenerator* g1 = new GravityGenerator(Vector3(0, -9.8, 0));
	ps->addForce(g1);
	ps->registerParticle(g1, p3);
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
	ps = new ParticleSystem();

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
	
	
	/*auto g2 = ps->addUniformGenerator(Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0f ,100 , 0.01f, 25.0f, spawn_position_distribution::UNIFORM_SP, 1000.0f, 50, Vector4(0, 1, 0, 1));
	auto g1 = ps->addUniformGenerator(Vector3(0, 0, 0), Vector3(0, 0, 0), 0.01f ,100 , 0.01f, 15.0f, spawn_position_distribution::UNIFORM_SP, 1000.0f, 50, Vector4(1, 1, 0, 1));
	eg = new ExplosionGenerator(5000.0f, 100.0f, 0.25f);
	ps->addForce(eg);
	ps->addLink(eg, g1);*/
	
	
	//auto grav1 = ps->addForce(new GravityGenerator(Vector3(0, 50, 0)));
	////ps->addWind(Vector3(0, 50, 0), Vector3(100, 30, 100), Vector3(5, 1, -5), 0.25f);
	//auto t = ps->addForce(new TorbellinoGenerator(Vector3(0, 50, 0), Vector3(3000, 5000, 3000), 0.25, 2.0f));
	//Se linkean fuerzas y particulas
	//ps->addRegister(grav1, g1);
	//ps->addRegister(t, g2);

	#pragma endregion

	#pragma region PRACTICA 4

	generateSpringDemo();
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
	ps->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	//deregisterAxis();

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
		ac1->getK() += 0.1;
		break;
	case 'K':
		ac1->getK() -= 0.1;
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