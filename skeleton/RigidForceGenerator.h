#pragma once
#include <PxPhysicsAPI.h>
#include "DynamicObject.h"

using namespace physx;

class RigidForceGenerator {
protected:
    bool _isActive = true;
public:
    virtual void applyForce(DynamicObject* obj, double t) = 0;
    virtual ~RigidForceGenerator() {}

    bool isActive() const { return _isActive; }
    void setActive(bool b) { _isActive = b; }
};
