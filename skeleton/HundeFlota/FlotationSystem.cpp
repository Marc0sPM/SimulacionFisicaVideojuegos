#include "FlotationSystem.h"
#include <iostream>

FlotationSystem::FlotationSystem(Vector3 pos, Vector3 liquidSize, float liquidDensity, Vector4 liquidColor)
{
    _liquidLevel = pos.y + liquidSize.y / 2;
    _liquidDensity = liquidDensity;
    _liquid = new GameObject(pos, &PxBoxGeometry(liquidSize), liquidColor, rb_type::NONE);
    _liquid->init_render();
}

void FlotationSystem::applyForce(DynamicObject* obj, double t) {
    Vector3 size = obj->getBoxSize();  // Half extents
    float objHeight = size.y * 2;  // Altura completa del objeto
    float objVolume = size.x * 2 * size.y * 2 * size.z * 2;  // Volumen completo
    float objPosY = obj->getRB()->getGlobalPose().p.y;

    // Calcular el nivel de inmersión, desde el punto más bajo del objeto
    float immersed_level = (_liquidLevel - (objPosY - size.y)) / objHeight;

    // Asegurarnos de que el nivel de inmersión esté en el rango [0, 1]
    if (immersed_level < 0.0f) immersed_level = 0.0f;  // Totalmente fuera del agua
    else if (immersed_level > 1.0f) immersed_level = 1.0f;  // Totalmente sumergido

    // Calcular la fuerza de flotación
    float buoyancy_force = _liquidDensity * objVolume * immersed_level * _gravity.magnitude();

    // Aplicar la fuerza de flotación sobre el objeto
    obj->addForce({ 0, buoyancy_force, 0 });

    //// Damping vertical
    //float dampingFactor = 0.2f;
    //float velocityY = obj->getRB()->getLinearVelocity().y;
    //float damping = -dampingFactor * velocityY;

    //obj->addForce({ 0, damping, 0 });  // Aplicar el damping vertical
}
