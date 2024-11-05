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
				applyForces(*it, t);
				(*it)->update(t, Particle::_EULER_SEMI, *this);
			}
			++it; 
		}
	}
	//Eliminacion particulas
	for (auto p : toErase) {
		auto it = std::find(pList.begin(), pList.end(), p);
		if (it != pList.end()) {
			pList.erase(it); 
			delete p;
		}
	}
	//Eliminacion fuerzas
	for (auto f : fToErase) {
		auto it = std::find(fList.begin(), fList.end(), f);
		if (it != fList.end()) {
			fList.erase(it);
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

void ParticleSystem::addFireWorkGenerator(Vector3 pos, Vector3 direction, float mass,float rate, int particle_count, float spawnR, spawn_position_distribution sp, float rat, float lifetime, Vector4 color)
{
	// Crear una partícula base con las propiedades de la explosión
	Particle p = Particle(pos, direction);
	p.setRatius(rat);
	p.setLifeTime(lifetime);
	p.setColor(color);
	p.setMass(mass);

	// Crear el generador de explosiones y añadirlo a la lista de generadores
	gList.push_back(new FireWorkGenerator(&p,rate, particle_count, spawnR, sp));
}

void ParticleSystem::addGravity(Vector3 grav) {
	fList.push_back(new GravityGenerator(grav));
}

void ParticleSystem::addWind(Vector3 center, Vector3 size, Vector3 windVel, float rCoef)	{
	fList.push_back(new WindGenerator(center, size, windVel, rCoef));
}

void ParticleSystem::addTorbellino(Vector3 center, Vector3 size, float rozCoef, float intensity)
{
	fList.push_back(new TorbellinoGenerator(center, size, rozCoef, intensity));
}

void ParticleSystem::addExplosion(Vector3 center, float k, float r, float tau)
{
	fList.push_back(new ExplosionGenerator(center, k, r, tau));
}

void ParticleSystem::applyForces(Particle* p, double t)
{
	Vector3 totalForce = Vector3(0, 0, 0);
	for (auto f : fList) {
		if (f) {
			if (f->isAlive()) {
				totalForce += f->calculateForce(p);
				f->update(t);
			}
			else	fToErase.push_back(f);
		}
	}
	//std::cout<< "Vector3(" << totalForce.x << ", " << totalForce.y << ", " << totalForce.z << ")\n";
	p->setForce(totalForce);

}
