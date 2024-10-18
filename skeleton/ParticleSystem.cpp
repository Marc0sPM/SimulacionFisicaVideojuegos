#include "ParticleSystem.h"

void ParticleSystem::update(double t) {

	toErase.clear();

	for (auto g : gList) {
		if(g != nullptr)
			g->update(t, *this);
	}

	for (auto it = pList.begin(); it != pList.end(); ) {
		if (*it != nullptr) {
			(*it)->update(t, Particle::_EULER_SEMI, *this);
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

void ParticleSystem::addGenerator(Vector3 pos, Vector3 direction, float rate, generators_type type, float range)
{
	Particle p = Particle(pos, direction);
	switch (type)
	{
	case UNIFORM:
		gList.push_back(new UniformGenerator(p, rate, range));
		break;
	case NORMAL:
		gList.push_back(new NormalGenerator(p, rate, Vector3(0, 60, 0), Vector3(8, 0.5, 8)));
		break;
	default:
		break;
	}
}
