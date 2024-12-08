#include "FlotationSystem.h"
#include <iostream>

FlotationSystem::FlotationSystem(Vector3 pos, Vector3 liquidSize, float liquidDensity, Vector4 liquidColor)
{
    _liquidLevel = pos.y + liquidSize.y - 2;
    _liquidDensity = liquidDensity;
    _liquid = new GameObject(pos, &PxBoxGeometry(liquidSize), liquidColor, rb_type::NONE);
    _liquid->init_render();
}

void FlotationSystem::applyForce(DynamicObject* obj, double t) {
   
    Vector3 liquidSize = _liquid->getBoxSize() * 2;         
    Vector3 liquidPos = _liquid->getPosition();             // Centro del líquido  
    float liquidBottom = liquidPos.y - liquidSize.y / 2;    // Parte baja del líquido 

    // Obtener la posición y dimensiones del objeto
    Vector3 size = obj->getBoxSize(); // Half extents 
    float objHeight = size.y * 2; 
    float objVolume = size.x * 2 * size.y * 2 * size.z * 2; 
    Vector3 objPos = obj->getRB()->getGlobalPose().p; // Centro del objeto 

    // Verificar si el objeto está dentro del volumen del líquido
    bool isWithinLiquid = 
        objPos.x + size.x > liquidPos.x - liquidSize.x / 2 &&   // Dentro del rango X 
        objPos.x - size.x < liquidPos.x + liquidSize.x / 2 && 
        objPos.z + size.z > liquidPos.z - liquidSize.z / 2 &&   // Dentro del rango Z 
        objPos.z - size.z < liquidPos.z + liquidSize.z / 2 && 
        objPos.y - size.y < _liquidLevel &&                     // Parte baja del objeto dentro o  por debajo de la superficie
        objPos.y + size.y > liquidBottom;                       // Parte alta del objeto por encima de la parte baja del líquido

    if (!isWithinLiquid) {
      
        return;
    }


    float immersed_level = (_liquidLevel - (objPos.y - size.y)) / objHeight;

    // clamp en el rango [0, 1]
    if (immersed_level < 0.0f) immersed_level = 0.0f;  // Totalmente fuera del agua
    else if (immersed_level > 1.0f) immersed_level = 1.0f;  // Totalmente sumergido

   
    float buoyancy_force = _liquidDensity * objVolume * immersed_level * _gravity.magnitude();

   
    obj->addForce({ 0, buoyancy_force, 0 });

}
