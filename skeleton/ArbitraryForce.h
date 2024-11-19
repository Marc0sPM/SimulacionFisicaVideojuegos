#pragma once
#include "ForceGenerator.h"
class ArbitraryForce : public ForceGenerator
{
public:
	ArbitraryForce(Vector3 force, float dur)
		: _force(force) {
		duration = dur;
	}

	void update(double t) override {
		if (active) {
			_force_dur -= t;
			if (_force_dur < 0) active = false;
		}
	}

	void apply() {
		active = true;
		_force_dur = duration;
	}

	Vector3 calculateForce(Particle* p) override {
		if(active) return _force;
		return Vector3(0, 0, 0);
	}

	void changeForce(Vector3 newForce) {
		_force = newForce;
	}
private:
	Vector3 _force;
	bool active = false;
	float _force_dur;
};
