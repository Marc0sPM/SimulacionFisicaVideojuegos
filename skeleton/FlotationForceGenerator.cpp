#include "FlotationForceGenerator.h"

FlotationForceGenerator::FlotationForceGenerator(float liquidLevel, Vector3 objectSize, float liquidDensity)
    : _liquidLevel(liquidLevel),
    _objectHeight(objectSize.y),
    _objectVolume(objectSize.x* objectSize.y* objectSize.z),
    _liquidDensity(liquidDensity) {}

FlotationForceGenerator::~FlotationForceGenerator() {}

Vector3 FlotationForceGenerator::calculateForce(Particle* p) {
    // Obtener la posici�n vertical del objeto y calcular la inmersi�n.
    float objectPositionY = p->getPosition().y;
    float immersedFraction = 0.0f;

    if (objectPositionY - _liquidLevel > _objectHeight * 0.5f) {
        // Caso 1: El objeto est� completamente fuera del l�quido.
        immersedFraction = 0.0f;
    }
    else if (_liquidLevel - objectPositionY > _objectHeight * 0.5f) {
        // Caso 2: El objeto est� completamente sumergido.
        immersedFraction = 1.0f;
    }
    else {
        // Caso 3: El objeto est� parcialmente sumergido.
        immersedFraction = (_liquidLevel - objectPositionY) / _objectHeight + 0.5f;
    }

    // Calcular la fuerza de flotaci�n.
    float buoyancyForce = _liquidDensity * _objectVolume * immersedFraction * _gravity;

    // Retornar el vector de fuerza (solo act�a en el eje Y).
    return Vector3(0.0f, buoyancyForce, 0.0f);
}

void FlotationForceGenerator::updateLiquidLevel(float newLevel) {
    _liquidLevel = newLevel;
}