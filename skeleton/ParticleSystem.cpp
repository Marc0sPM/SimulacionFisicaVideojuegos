#include "ParticleSystem.h"

void ParticleSystem::update(double t) {

	toErase.clear();

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
	//Eliminacion particulas
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
	// Crear una part�cula base con las propiedades de la explosi�n
	Particle p = Particle(pos, direction);
	p.setRatius(rat);
	p.setLifeTime(lifetime);
	p.setColor(color);
	p.setMass(mass);

	// Crear el generador de explosiones y a�adirlo a la lista de generadores
	gList.push_back(new ExplosionGenerator(&p,rate, particle_count, spawnR, sp));
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

void ParticleSystem::applyForces(Particle* p)
{
	Vector3 totalForce = Vector3(0, 0, 0);
	for (auto f : fList) {
		totalForce += f->calculateForce(p);
	}
	//std::cout<< "Vector3(" << totalForce.x << ", " << totalForce.y << ", " << totalForce.z << ")\n";
	p->setForce(totalForce);

}
