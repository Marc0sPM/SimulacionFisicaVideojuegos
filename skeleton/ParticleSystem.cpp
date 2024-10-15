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
			++it;  // Mueve al siguiente elemento
		}
	}

	// Eliminar partículas en `toErase`
	for (auto p : toErase) {
		auto it = std::find(pList.begin(), pList.end(), p); // Busca la partícula
		if (it != pList.end()) {
			pList.erase(it); // Elimina la partícula
			delete p;
		}
	}
}

void ParticleSystem::addGenerator(Vector3 pos, float rate, generators_type type)
{
	switch (type)
	{
	case UNIFORM:
		gList.push_back(new UniformGenerator(pos, rate, Vector3(-20, 20, 0), Vector3(20, 30, 0)));
		break;
	case NORMAL:
		break;
	default:
		break;
	}
}
