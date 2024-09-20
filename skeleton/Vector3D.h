#pragma once
#include <algorithm>

template <typename T>

class Vector3D
{
public:
	T x, y, z;
	Vector3D() {}
	Vector3D(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {
	}

	T module() {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	Vector3D normalize() {
		T mod = module();
		return Vector3D(x / mod, y / mod, z / mod);
	}
	// Producto vectorial
	T dot(const Vector3D& v) {
		return v.x * x + v.y * y + v.z * z;
	}

	Vector3D& operator *(T num) { 
		x *= num;
		y *= num;
		z *= num;
		return *this;
	}

	Vector3D& operator =(const Vector3D& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	Vector3D operator+(const Vector3D& v) {
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}

	Vector3D operator-(const Vector3D& v) {
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}

	Vector3D operator *(const Vector3D& v) {
		return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

