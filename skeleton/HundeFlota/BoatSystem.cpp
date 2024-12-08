#include "BoatSystem.h"
#include "HF_Scene.h"

void BoatSystem::update(double t)
{
	_counter -= t;
	if (_counter < 0) {
		generateBoat();
		_counter = SPAWN_TIME; 
	}

	Vector3 waterPos = _water->getLiquidPos();
	Vector3 waterSize = _water->getLiquidSize();
	for (auto b : _boats) {
		checkLimits(b, waterPos, waterSize ); 
		moveBoat(b);

	}

	for (auto& boat : _remove_boats) {
 		_boats.remove(boat);
		_sys->removeObject(boat);
		delete boat;
	}

	_remove_boats.clear();
}

#pragma region AUXILIAR METHODS & FUNCS

void BoatSystem::generateBoat() {
	if (_boats.size() < MAX_BOATS) {
		Vector2 pos; 
		bool isValidPos = false;

		// Obtener la posición del punto inferior izquierdo del líquido
		Vector3 liquidPos = _water->getLiquidPos();
		Vector3 liquidSize = _water->getLiquidSize(); // Dimensiones completas del líquido

		float minX = liquidPos.x - liquidSize.x / 2 + BOAT_SIZE.x; // borde izquierdo
		float maxX = liquidPos.x + liquidSize.x / 2 - BOAT_SIZE.x; // borde derecho
		float minZ = liquidPos.z - liquidSize.z / 2 + BOAT_SIZE.z; // borde inferior
		float maxZ = liquidPos.z + liquidSize.z / 2 - BOAT_SIZE.z; // borde superior

		// Generar posición aleatoria dentro de la superficie del agua
		while (!isValidPos) {
			pos.x = minX + (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * (maxX - minX);
			pos.y = minZ + (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * (maxZ - minZ);

			// Comprobamos que no exista ningun barco en esa posicion en el eje z
			isValidPos = !isOverlapping(pos);

			if (isValidPos) {
				Boat* boat = new Boat(_physics, _scene, Vector3(pos.x, _spawnHeight, pos.y), BOAT_SIZE, GenerateRandomColor(), calculateRandomMass());
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
		float minZ = BOAT_SIZE.z  + 3.0f;

		Vector3 bpos = b->getRB()->getGlobalPose().p;
		if (std::abs(pos.y - bpos.z) < minZ) {
			return true;
		}
	}
	return false;
}

float BoatSystem::calculateRandomMass()
{
	return MIN_MASS + static_cast<float>(std::rand()) / RAND_MAX * (MAX_MASS - MIN_MASS);
}

void BoatSystem::moveBoat(Boat* boat)
{
	Vector3 desiredVelocity(boat->speed, 0, 0); 
	Vector3 currentVelocity = boat->getRB()->getLinearVelocity(); 
	Vector3 force = (desiredVelocity - currentVelocity) * boat->getRB()->getMass(); // F = m * a

	boat->addForce(force);
}
void BoatSystem::checkLimits(Boat* boat, Vector3 waterPos, Vector3 waterSize)
{
	// Limites del agua en el eje X
	float minX = waterPos.x - waterSize.x / 2 + BOAT_SIZE.x;
	float maxX = waterPos.x + waterSize.x / 2 - BOAT_SIZE.x;

	// Posición actual del barco
	float boatX = boat->getRB()->getGlobalPose().p.x;

	if (boatX <= minX && boat->direction != move_dir::RIGHT) {
		boat->direction = move_dir::RIGHT; // Cambiar dirección a la derecha 
		boat->speed = std::abs(boat->speed); // Asegurarse de que la velocidad sea positiva
	}
	else if (boatX >= maxX && boat->direction != move_dir::LEFT) {
		boat->direction = move_dir::LEFT;  // Cambiar dirección a la izquierda 
		boat->speed = -std::abs(boat->speed); // Asegurarse de que la velocidad sea negativa
	}
}

void BoatSystem::removeBoat(Boat* boat) {
	if (std::find(_remove_boats.begin(), _remove_boats.end(), boat) == _remove_boats.end()) {
		_remove_boats.push_back(boat);
		_hf_scene->spawnFrags(boat);
	}
}
#pragma endregion