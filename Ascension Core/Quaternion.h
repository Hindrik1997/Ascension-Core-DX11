#pragma once
#include "Vector3f.h"

class Quaternion
{
public:
	float x, y, z, w;

	Quaternion(float _x, float _y, float _z, float _w);
	Quaternion();
	~Quaternion();
};

float Length(Quaternion quat);
Quaternion Normalize(Quaternion quat);
Quaternion Conjugate(Quaternion quat);
Quaternion Multiply(Quaternion A, Quaternion B);

//Angle is in euler angles
Quaternion RotatePointOverAxis(float angle, Vector3f axis, Vector3f point);