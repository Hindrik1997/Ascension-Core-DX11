#pragma once
#include "Vector3f.h"
#include <iostream>
#include "Quaternion.h"
#include <DirectXMath.h>

using namespace std;
using namespace DirectX;

class GameObject;

class Transform
{
public:
	//Position of the object
	Vector3f Position = Vector3f(0.0f, 0.0f,0.0f);

	//Rotation is the rotation of the local axis relative to the world
	Quaternion Rotation = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);

	//Scale of the object in local axis
	Vector3f Scale = Vector3f(1.0f, 1.0f, 1.0f);

	void RotateToWorldAxisX(float angle);
	void RotateToWorldAxisY(float angle);
	void RotateToWorldAxisZ(float angle);

	void RotateToLocalAxisX(float angle);
	void RotateToLocalAxisY(float angle);
	void RotateToLocalAxisZ(float angle);

	void MoveToWorldAxisX(float amount);
	void MoveToWorldAxisY(float amount);
	void MoveToWorldAxisZ(float amount);

	void MoveToLocalAxisX(float amount);
	void MoveToLocalAxisY(float amount);
	void MoveToLocalAxisZ(float amount);

	XMMATRIX GetWorldMatrix();

	Transform();
	~Transform();

	friend ostream& operator << (ostream& os, const Transform& t);
};