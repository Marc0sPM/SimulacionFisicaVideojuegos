#include "ParticleSystem.h"

void ParticleSystem::update(double t) {

	toErase.clear();
	fToErase.clear();
	//Generadores
	for (auto g : gList) {
		if(g != nullptr)
			g->update(t, *this);
	}
	
	//Particulas
	for (auto it = pList.begin(); it != pList.end(); ) {
		if (*it != nullptr) {
			if ((*it)->canDie()) {
				killParticle(*it);
			}
			else {
				applyForces(*it);
				(*it)->update(t, Particle::_EULER_SEMI, *this);
			}
			++it; 
		}
	}
	//Actualizacion de generadores de fuerzas
	for (auto& pair : forceRegister) {
		auto fG = pair.first;
		if (fG != nullptr) {
			fG->update(t);
		}
	}
	//Eliminacion particulas
	for (auto p : toErase) {
		auto it = std::find(pList.begin(), pList.end(), p);
		if (it != pList.end()) {
			pList.erase(it); 
		}
		for (auto& entry : forceRegister) {
			entry.second.remove(p);
		}
		delete p;  
	}

	//Eliminacion fuerzas
	for (auto f : fToErase) {
		auto it = forceRegister.find(f); 

		if (it != forceRegister.end()) {
			it->second.clear();
			forceRegister.erase(it);
			delete f;
		}
	}
}

void ParticleSystem::killParticle(Particle* p) {
	if (p != nullptr && p->getIterator() != pList.end())
		toErase.push_back(p);
}

void ParticleSystem::addParticle(Particle* p) {
	pList.push_back(p);
	p->setIterator(--pList.end());
}

ParticleGenerator* ParticleSystem::addUniformGenerator(Vector3 pos, Vector3 direction,float mass ,float rate, float range, float spawnR, spawn_position_distribution sp, float rat, float lifetime, Vector4 color)
{
	Particle p = Particle(pos, direction);
	p.setRatius(rat);
	p.setLifeTime(lifetime);
	p.setColor(color);
	p.setMass(mass);

	gList.push_back(new UniformGenerator(&p, rate, range, spawnR, sp));
	return gList.back();
}

ParticleGenerator* ParticleSystem::addNormalGenerator(Vector3 pos, Vector3 direction,float mass ,float rate, Vector3 dev, float spawnR, spawn_position_distribution sp, float rat, float lifetime, Vector4 color)
{
	Particle p = Particle(pos, direction);
	p.setRatius(rat);
	p.setLifeTime(lifetime);
	p.setColor(color);
	p.setMass(mass);

	gList.push_back(new NormalGenerator(&p, rate, dev, spawnR, sp));
	return gList.back();
}

ParticleGenerator* ParticleSystem::addFireWorkGenerator(Vector3 pos, Vector3 direction, float mass,float rate, int particle_count, float spawnR, spawn_position_distribution sp, float rat, float lifetime, Vector4 color)
{
	// Crear una partícula base con las propiedades de la explosión
	Particle p = Particle(pos, direction);
	p.setRatius(rat);
	p.setLifeTime(lifetime);
	p.setColor(color);
	p.setMass(mass);

	// Crear el generador de explosiones y añadirlo a la lista de generadores
	gList.push_back(new FireWorkGenerator(&p,rate, particle_count, spawnR, sp));
	return gList.back();
}


ForceGenerator*  ParticleSystem::addExplosionGenerator(float k, float r, float tau)
{
	ExplosionGenerator* eg = new ExplosionGenerator(k, r, tau);
	forceRegister.insert({eg, std::list<Particle* >() });
	return eg;

}

ForceGenerator* ParticleSystem::findForce(force_type type) {
	for (auto it : forceRegister) {
		if (it.first->getType() == type) return it.first;
	}
	return nullptr;
}

void ParticleSystem::applyForces(Particle* p)
{
	Vector3 totalForce = Vector3(0, 0, 0);

	for (auto& entry : forceRegister) {
		ForceGenerator* generator = entry.first;          
		std::list<Particle*>& particles = entry.second;  

		if (std::find(particles.begin(), particles.end(), p) != particles.end()) {
			if (generator->isAlive()) {
				totalForce += generator->calculateForce(p);  
			}
		}
	}
	p->setForce(totalForce);
}

void ParticleSystem::addLink(ForceGenerator* fg, ParticleGenerator* pg)	{
	pg->linkForce(fg);
}

void ParticleSystem::registerParticle(ForceGenerator* fg, Particle* p) {
	auto it = forceRegister.find(fg);
	it->second.push_back(p);
}

ForceGenerator* ParticleSystem::addForce(ForceGenerator* fg) {
	forceRegister.insert({ fg, std::list<Particle* >() });
	return fg;
}

void ParticleSystem::generateSpringDemo()
{
	// Ejercicio 2
	Particle* p1 = new Particle(Vector3( - 10.0, 10.0, 0.0 ), Vector3(0.0, 0.0, 0.0), Vector3(0,0,0), Vector4(0.5, 0.0, 1.0, 1.0));
	p1->setLifeTime(100);
	p1->setRatius(1000);
	p1->setMass(2.0f);

	Particle* p2 = new Particle(Vector3(10.0, 10.0, 0.0 ), Vector3(0.0, 0.0, 0.0), Vector3(0, 0, 0), Vector4(1.0, 0.5, 0.0, 1.0));
	p2->setRatius(1000);
	p2->setLifeTime(100);
	p2->setMass(2.0f);

	addParticle(p1);
	addParticle(p2);

	SpringForceGenerator *sp1 = new SpringForceGenerator(0.98, 10, p2);
	SpringForceGenerator* sp2 = new SpringForceGenerator(0.98, 10, p1);

	addForce(sp1);
	addForce(sp2);

	registerParticle(sp1, p1);
	registerParticle(sp2, p2);

	//Ejercicio 1
	Particle* p3 = new Particle(Vector3(0.0, 30.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0, 0, 0), Vector4(1.0, 0.5, 0.0, 1.0));
	p3->setLifeTime(1000);
	p3->setRatius(1000);
	p3->setMass(2.0);

	addParticle(p3);

	AnchoredSpringFG* ac1 = new AnchoredSpringFG(1, 20, Vector3(0, 30, 0));
	addForce(ac1);

	registerParticle(ac1, p3);

	GravityGenerator* g1 = new GravityGenerator(Vector3(0, -9.8, 0));
	addForce(g1);
	registerParticle(g1, p3);
}

