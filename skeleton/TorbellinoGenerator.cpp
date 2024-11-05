#include "TorbellinoGenerator.h"

void TorbellinoGenerator::calculateVelocity(Vector3 pPos)
{
	Vector3 aux = {
		- (pPos.z - center.z),
		0,						// Preguntar que narices poner aqui
		pPos.x - center.x
	};
	windVelocity = intensity * aux;
}
