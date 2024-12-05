#include "BoatSystem.h"

void BoatSystem::generateBoat() {
	if (_boats.size() < MAX_BOATS) {
		Vector2 pos; 
		bool isValidPos = false;

		//Calculamos posicion aleatoria
		while (!isValidPos) {

			pos.x = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * _surface_size.x;
			pos.y = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * _surface_size.y;


			isValidPos = !isOverlapping(pos);

			if (isValidPos) {
				Boat* boat = new Boat(_physics, _scene, Vector3(pos.x, SPAWN_HEIGHT, pos.y), BOAT_SIZE, GenerateRandomColor(), calculateRandomMass());
				_boats.push_back(boat);
				_sys->addDynamic(boat);
				_sys->registerObject(_water, boat);
				return;
			}
		}
	}
	else {
		std::cout << "ERROR: Numero de barcos es mayor a " << MAX_BOATS << "\n\n";
	}
}

bool BoatSystem::isOverlapping(Vector2 pos) {
	for (auto& b : _boats) {
		Vector3 bsize = b->getBoxSize();
		float minX = bsize.x + 2; 
		float minZ = bsize.z + 2;

		Vector3 bpos = b->getRB()->getGlobalPose().p;
		if (std::abs(pos.x - bpos.x) < minX && std::abs(pos.y - bpos.z) <minZ) {
			return true;  // Hay solapamiento
		}
	}
	return false;
}

float BoatSystem::calculateRandomMass()
{
	return MIN_MASS + static_cast<float>(std::rand()) / RAND_MAX * (MAX_MASS - MIN_MASS);
}
