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
    float immersed_level= 0.0f;

    if (objectPositionY - _liquidLevel > _objectHeight * 0.5f) {
        // Completamente fuera
        immersed_level = 0.0f;
    }
    else if (_liquidLevel - objectPositionY > _objectHeight * 0.5f) {
        // Completamente sumergido
        immersed_level = 1.0f;
    }
    else {
        // Parcialmente sumergido.
        immersed_level = (_liquidLevel - objectPositionY) / _objectHeight + 0.5f;
    }

    float buoyancy_force = _liquidDensity * _objectVolume * immersed_level * _gravity;

    
    return Vector3(0.0f, buoyancy_force, 0.0f);
}