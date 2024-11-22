#include "TorbellinoGenerator.h"

void TorbellinoGenerator::calculateVelocity(Vector3 pPos)
{
	Vector3 aux = {
		- (pPos.z - center.z),
		100 - (pPos.y -  center.y),						// Preguntar que narices poner aqui
		pPos.x - center.x
	};
	windVelocity = intensity * aux;
}
