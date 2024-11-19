#include "FlotationForceGenerator.h"

FlotationForceGenerator::FlotationForceGenerator(float liquidLevel, Vector3 objectSize, float liquidDensity)
    : _liquidLevel(liquidLevel),
    _objectHeight(objectSize.y),
    _objectVolume(objectSize.x* objectSize.y* objectSize.z),
    _liquidDensity(liquidDensity) {}

FlotationForceGenerator::~FlotationForceGenerator() {}

Vector3 FlotationForceGenerator::calculateForce(Particle* p) {
    // Obtener la posición vertical del objeto y calcular la inmersión.
    float objectPositionY = p->getPosition().y;
    float immersedFraction = 0.0f;

    if (objectPositionY - _liquidLevel > _objectHeight * 0.5f) {
        // Caso 1: El objeto está completamente fuera del líquido.
        immersedFraction = 0.0f;
    }
    else if (_liquidLevel - objectPositionY > _objectHeight * 0.5f) {
        // Caso 2: El objeto está completamente sumergido.
        immersedFraction = 1.0f;
    }
    else {
        // Caso 3: El objeto está parcialmente sumergido.
        immersedFraction = (_liquidLevel - objectPositionY) / _objectHeight + 0.5f;
    }

    // Calcular la fuerza de flotación.
    float buoyancyForce = _liquidDensity * _objectVolume * immersedFraction * _gravity;

    // Retornar el vector de fuerza (solo actúa en el eje Y).
    return Vector3(0.0f, buoyancyForce, 0.0f);
}

void FlotationForceGenerator::updateLiquidLevel(float newLevel) {
    _liquidLevel = newLevel;
}