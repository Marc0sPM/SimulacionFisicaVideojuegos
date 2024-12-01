#pragma once
#include "RigidForceGenerator.h"
class RWindGenerator : public RigidForceGenerator
{
private:
    Vector3 _velocity;
    float  _rozCoef; 

public:
    RWindGenerator(const Vector3& velocity,  float rozCoef)
        : _velocity(velocity), _rozCoef(rozCoef) {

        _isActive = true;
    }

    void applyForce(DynamicObject* obj, double t) override {
        if (_isActive && obj->getRB() != nullptr) {
            Vector3 force = _rozCoef * (_velocity - obj->getLinearVelocity());
            obj->getRB()->addForce(force); 
        }
    }
};

