#ifndef _VEC3_HPP_
#define _VEC3_HPP_

#include <iostream>

struct vec3
{
	float x, y, z;

	vec3() : x(0), y(0), z(0) {}
	vec3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

	vec3 operator+(const vec3& ext) {
		return vec3(x + ext.x, y + ext.y, z + ext.z);
	}

	vec3 operator-(const vec3& ext) {
		return vec3(x - ext.x, y - ext.y, z - ext.z);
	}

	vec3 operator*(const float& ext) {
		return vec3(ext * x, ext * y, ext * z);
	}

	friend std::ostream& operator<< (std::ostream& out, const vec3& vector)
	{
		out << vector.x << " " << vector.y << " " << vector.z;
		return out;
	}

	float len() {
		return (float)sqrt(pow(x, 2.f) + pow(y, 2.f) + pow(z, 2.f));
	}
};

#endif