#include "SpringDemo.h"
#include "ParticleSystem.h"

SpringDemo::SpringDemo(ParticleSystem* ps)
{
	_ps = ps;
}
void SpringDemo::init()
{
	g1 = new GravityGenerator(Vector3(0, -9.8, 0));
	_ps->addForce(g1);

	//Ejercicio 1
	// anchoredSpring();

	//Ejercicio 2
	 particleSpring();

	//Ejercicio 2 - opcional
	// createSlink();

	// Ejercicio 3
	//flotationSystem();
}

void SpringDemo::createSlink() {

	//Particle 1
	_slink.s_p1 = new Particle(Vector3(0.0, 30.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0, 0, 0), Vector4(1.0, 0.0, 0.0, 1.0));
	_slink.s_p1->setLifeTime(_slink.life);
	_slink.s_p1->setRatius(10000);
	_slink.s_p1->setMass(2.0);
	_ps->addParticle(_slink.s_p1);
	// Particle 2
	_slink.s_p2 = new Particle(Vector3(0.0, 30.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0, 0, 0), Vector4(1.0, 0.5, 0.0, 1.0));
	_slink.s_p2->setLifeTime(_slink.life);
	_slink.s_p2->setRatius(10000);
	_slink.s_p2->setMass(2.0);
	_ps->addParticle(_slink.s_p2);

	// Particle 3
	_slink.s_p3 = new Particle(Vector3(0.0, 30.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0, 0, 0), Vector4(1.0, 0.0, 1.0, 1.0));
	_slink.s_p3->setLifeTime(_slink.life);
	_slink.s_p3->setRatius(10000);
	_slink.s_p3->setMass(2.0);
	_ps->addParticle(_slink.s_p3);

	// Particle 4
	_slink.s_p4 = new Particle(Vector3(0.0, 30.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0, 0, 0), Vector4(0.0, 1.0, 0.0, 1.0));
	_slink.s_p4->setLifeTime(_slink.life);
	_slink.s_p4->setRatius(10000);
	_slink.s_p4->setMass(2.0);
	_ps->addParticle(_slink.s_p4);
	

	// Anchored Spring
	_slink.an_k = 10;
	_slink.an_l = 10;

	_slink.s_an = new AnchoredSpringFG(_slink.an_k, _slink.an_l, Vector3(0, 30, 0));
	_slink.s_an->setAnchorLife(_slink.life);
	_ps->addForce(_slink.s_an);
	_ps->registerParticle(_slink.s_an, _slink.s_p1);
	
	//Spring 1
	_slink.k1 = 20;
	_slink.l1 = 5;

	_slink.s_sp1_2 = new SpringForceGenerator(_slink.k1, _slink.l1, _slink.s_p2);
	_slink.s_sp2_1 = new SpringForceGenerator(_slink.k1, _slink.l1, _slink.s_p1);

	_ps->addForce(_slink.s_sp1_2);
	_ps->addForce(_slink.s_sp2_1);

	_ps->registerParticle(_slink.s_sp1_2, _slink.s_p1);
	_ps->registerParticle(_slink.s_sp2_1, _slink.s_p2);

	//Spring 2
	_slink.k2 = 50;
	_slink.l2 = 40;

	_slink.s_sp2_3 = new SpringForceGenerator(_slink.k2, _slink.l2, _slink.s_p3);
	_slink.s_sp3_2 = new SpringForceGenerator(_slink.k2, _slink.l2, _slink.s_p2);

	_ps->addForce(_slink.s_sp2_3);
	_ps->addForce(_slink.s_sp3_2);

	_ps->registerParticle(_slink.s_sp2_3, _slink.s_p2);
	_ps->registerParticle(_slink.s_sp3_2, _slink.s_p3);

	//Spring 3
	_slink.k3 = 5;
	_slink.l3 = 100;

	_slink.s_sp3_4 = new SpringForceGenerator(_slink.k3, _slink.l3, _slink.s_p4);
	_slink.s_sp4_3 = new SpringForceGenerator(_slink.k3, _slink.l3, _slink.s_p3);

	_ps->addForce(_slink.s_sp3_4);
	_ps->addForce(_slink.s_sp4_3);

	_ps->registerParticle(_slink.s_sp3_4, _slink.s_p3);
	_ps->registerParticle(_slink.s_sp4_3, _slink.s_p4);
	
	_ps->registerParticle(g1, _slink.s_p1);
	_ps->registerParticle(g1, _slink.s_p2);
	_ps->registerParticle(g1, _slink.s_p3);
	_ps->registerParticle(g1, _slink.s_p4);

	
}

void SpringDemo::particleSpring()
{
	// Ejercicio 2
	p1 = new Particle(Vector3(-10.0, 10.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0, 0, 0), Vector4(0.5, 0.0, 1.0, 1.0));
	p1->setLifeTime(100);
	p1->setRatius(1000);
	p1->setMass(2.0f);

	p2 = new Particle(Vector3(10.0, 10.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0, 0, 0), Vector4(1.0, 0.5, 0.0, 1.0));
	p2->setRatius(1000);
	p2->setLifeTime(100);
	p2->setMass(2.0f);

	_ps->addParticle(p1);
	_ps->addParticle(p2);

	sp1 = new SpringForceGenerator(1.5, 10, p2);
	sp2 = new SpringForceGenerator(1.5, 10, p1);

	_ps->addForce(sp1);
	_ps->addForce(sp2);

	_ps->registerParticle(sp1, p1);
	_ps->registerParticle(sp2, p2);
}

void SpringDemo::anchoredSpring()
{
	p3 = new Particle(Vector3(0.0, 30.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0, 0, 0), Vector4(1.0, 0.5, 0.0, 1.0));
	p3->setLifeTime(1000);
	p3->setRatius(10000);
	p3->setMass(2.0);

	_ps->addParticle(p3);

	an1 = new AnchoredSpringFG(1, 20, Vector3(0, 30, 0));
	an1->setAnchorLife(1000);
	_ps->addForce(an1);
	_ps->registerParticle(an1, p3);

	_ps->registerParticle(g1, p3);

	Vector3 arb_force(3, 0, 0);
	ar1 = new ArbitraryForce(arb_force, 2);
	_ps->addForce(ar1);
	_ps->registerParticle(ar1, p3);
}

void SpringDemo::flotationSystem() {
	const float water_density = 1000.f;
	Vector3 obj_size = { 4.f, 4.f, 4.f };
	f_p1 = new Particle(Vector3(0, 40, 0), obj_size, { 1,0,0,1 }, shape::BOX);
	float perfect_mass = (obj_size.x * obj_size.y * obj_size.z) * water_density;
	float mass_offset = 4000;
	f_p1->setMass(mass_offset);
	f_p1->setLifeTime(1000);
	f_p1->setRatius(10000);

	_ps->addParticle(f_p1);

	float surface_height = 50.f;
	ffg = new FlotationForceGenerator(surface_height, obj_size, water_density);
	_ps->addForce(ffg);

	_ps->registerParticle(ffg, f_p1);
	_ps->registerParticle(g1, f_p1);
}
