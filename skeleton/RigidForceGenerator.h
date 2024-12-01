#pragma once
#include <PxPhysicsAPI.h>
#include "DynamicObject.h"

using namespace physx;

class RigidForceGenerator {
protected:
    bool _isActive;
public:
    virtual void applyForce(DynamicObject* obj, double t) = 0;
    virtual ~RigidForceGenerator() {}
};
