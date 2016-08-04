#pragma once
#include "Vector3f.h"

class Transform
{
public:
	Vector3f Position;
	Vector3f Rotation;
	Vector3f Scale;

	Transform();
	~Transform();
};