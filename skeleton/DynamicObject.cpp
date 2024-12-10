#include "DynamicObject.h"
#include <iostream>
DynamicObject::DynamicObject(PxPhysics* phy, PxScene* scene, Vector3 pos, PxGeometry* geo, Vector4 color, double mass) :
	GameObject(pos, geo, color, rb_type::DYNAMIC)
{

	_rb = phy->createRigidDynamic(_transform);
    

	_rb->attachShape(*_shape);
	
    // Calculo manual de la inercia
	Vector3 inertiaTensor = calculateInertiaTensor(mass);
	_rb->setMassSpaceInertiaTensor(inertiaTensor);
	_rb->setMass(mass);

    //Calculao de la inercia mediante physx
	// PxRigidBodyExt::updateMassAndInertia(*_rb, mass);
	scene->addActor(*_rb);

	init_render_RB(_rb);
}


Vector3 DynamicObject::calculateInertiaTensor(float mass)
{
    PxGeometryType::Enum gType = _shape->getGeometryType();

    switch (gType)
    {
        case PxGeometryType::eBOX: {
            PxBoxGeometry boxGeometry;
            _shape->getBoxGeometry(boxGeometry);
            float hx =  2 * boxGeometry.halfExtents.x;
            float hy = 2 * boxGeometry.halfExtents.y;
            float hz = 2 * boxGeometry.halfExtents.z;

            float Ixx = (1.0f / 12.0f) * mass * (hy * hy + hz * hz);
            float Iyy = (1.0f / 12.0f) * mass * (hx * hx + hz * hz);
            float Izz = (1.0f / 12.0f) * mass * (hx * hx + hy * hy);
            return PxVec3(Ixx, Iyy, Izz);
        }
        case PxGeometryType::eSPHERE: {
            //Dando por hecho que es una esfera solida
            PxSphereGeometry sphereGeometry;
            _shape->getSphereGeometry(sphereGeometry);
            float radius = sphereGeometry.radius;

            float I = (2.0f / 5.0f) * mass * radius * radius;
            return PxVec3(I, I, I);
        }
        case PxGeometryType::eCAPSULE: {
            PxCapsuleGeometry capsuleGeometry;
            _shape->getCapsuleGeometry(capsuleGeometry);
            float radius = capsuleGeometry.radius;
            float halfHeight = capsuleGeometry.halfHeight;

            float Ixx = (1.0f / 12.0f) * mass * (3 * radius * radius + 4 * halfHeight * halfHeight);
            float Izz = Ixx;
            float Iyy = (1.0f / 2.0f) * mass * radius * radius;
            return PxVec3(Ixx, Iyy, Izz);
        }
        default:
            // Si no se reconoce la geometría, retornar valores por defecto.
            return PxVec3(1.0f, 1.0f, 1.0f);
    }
}

