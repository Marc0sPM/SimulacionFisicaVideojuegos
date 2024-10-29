#include "ParticleSystem.h"

void ParticleSystem::update(double t) {

	toErase.clear();

	for (auto g : gList) {
		if(g != nullptr)
			g->update(t, *this);
	}

	for (auto it = pList.begin(); it != pList.end(); ) {
		if (*it != nullptr) {
			if ((*it)->canDie()) {
				killParticle(*it);
			}
			else {
				(*it)->update(t, Particle::_EULER_SEMI, *this);
				applyForces(*it);
			}
			++it; 
		}
	}

	for (auto p : toErase) {
		auto it = std::find(pList.begin(), pList.end(), p);
		if (it != pList.end()) {
			pList.erase(it); 
			delete p;
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

void ParticleSystem::addParticles(const std::vector<Particle*>& particles) {
	pList.insert(pList.end(), particles.begin(), particles.end());
}

void ParticleSystem::addUniformGenerator(Vector3 pos, Vector3 direction,float mass ,float rate, float range, float spawnR, spawn_position_distribution sp, float rat, float lifetime, Vector4 color)
{
	Particle p = Particle(pos, direction);
	p.setRatius(rat);
	p.setLifeTime(lifetime);
	p.setColor(color);
	p.setMass(mass);

	gList.push_back(new UniformGenerator(&p, rate, range, spawnR, sp));
}

void ParticleSystem::addNormalGenerator(Vector3 pos, Vector3 direction,float mass ,float rate, Vector3 dev, float spawnR, spawn_position_distribution sp, float rat, float lifetime, Vector4 color)
{
	Particle p = Particle(pos, direction);
	p.setRatius(rat);
	p.setLifeTime(lifetime);
	p.setColor(color);
	p.setMass(mass);

	gList.push_back(new NormalGenerator(&p, rate, dev, spawnR, sp));
}

void ParticleSystem::addExplosionGenerator(Vector3 pos, Vector3 direction, float mass,float rate, int particle_count, float spawnR, spawn_position_distribution sp, float rat, float lifetime, Vector4 color)
{
	// Crear una partícula base con las propiedades de la explosión
	Particle p = Particle(pos, direction);
	p.setRatius(rat);
	p.setLifeTime(lifetime);
	p.setColor(color);
	p.setMass(mass);

	// Crear el generador de explosiones y añadirlo a la lista de generadores
	gList.push_back(new ExplosionGenerator(&p,rate, particle_count, spawnR, sp));
}

void ParticleSystem::addGravity(Vector3 grav) {
	fList.push_back(new GravityGenerator(grav));
}

void ParticleSystem::applyForces(Particle* p)
{
	Vector3 accTotal = Vector3(0, 0, 0);
	for (auto f : fList) {
		accTotal += f->calculateAcc(p);
	}
	p->setAcceleration(accTotal);
}
