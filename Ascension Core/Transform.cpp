#include "Transform.h"
#include <string>
#include "GameObject.h"

void Transform::RotateToWorldAxisX(float angle)
{
	Rotation.x += angle;
}

void Transform::RotateToWorldAxisY(float angle)
{
	Rotation.y += angle;
}

void Transform::RotateToWorldAxisZ(float angle)
{
	Rotation.z += angle;
}

void Transform::RotateToLocalAxisX(float angle)
{

}

void Transform::RotateToLocalAxisY(float angle)
{

}

void Transform::RotateToLocalAxisZ(float angle)
{

}

void Transform::MoveToWorldAxisX(float amount)
{
	Position.x += amount;
}

void Transform::MoveToWorldAxisY(float amount)
{
	Position.y += amount;
}

void Transform::MoveToWorldAxisZ(float amount)
{
	Position.z += amount;
}

void Transform::MoveToLocalAxisX(float amount)
{
	XMMATRIX w = GetWorldMatrix();
	XMVECTOR v2 = XMVectorSet(amount, 0.0f, 0.0f, 0.0f);
	XMVECTOR posv = XMVector3Transform(v2, w);
	XMFLOAT3 pos2;
	XMStoreFloat3(&pos2, posv);
	Vector3f pos3 = Vector3f(pos2.x, pos2.y, pos2.z);
	Position = pos3;
}

void Transform::MoveToLocalAxisY(float amount)
{
	XMMATRIX w = GetWorldMatrix();
	XMVECTOR v2 = XMVectorSet(0.0f, amount, 0.0f, 0.0f);
	XMVECTOR posv = XMVector3Transform(v2, w);
	XMFLOAT3 pos2;
	XMStoreFloat3(&pos2, posv);
	Vector3f pos3 = Vector3f(pos2.x, pos2.y, pos2.z);
	Position = pos3;
}

void Transform::MoveToLocalAxisZ(float amount)
{
	XMMATRIX w = GetWorldMatrix();
	XMVECTOR v2 = XMVectorSet(0.0f, 0.0f, amount,  0.0f);
	XMVECTOR posv = XMVector3Transform(v2,w);
	XMFLOAT3 pos2;
	XMStoreFloat3(&pos2, posv);
	Vector3f pos3 = Vector3f(pos2.x, pos2.y, pos2.z);
	Position = pos3;
}


Transform::Transform() : Position(0.0f, 0.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f, 0.0f), Scale(1.0f, 1.0f, 1.0f)
{

}


Transform::~Transform()
{
}

ostream& operator<<(ostream & os, const Transform& t)
{
	os << "[" << to_string(t.Position.x) << " - " << to_string(t.Position.y) << " - " << to_string(t.Position.z) << "]" << endl;
	os << "[" << to_string(t.Rotation.x) << " - " << to_string(t.Rotation.y) << " - " << to_string(t.Rotation.z) << "]" << endl;
	os << "[" << to_string(t.Scale.x) << " - " << to_string(t.Scale.y) << " - " << to_string(t.Scale.z) << "]" << endl;
	return os;
}


XMMATRIX Transform::GetWorldMatrix()
{
	XMMATRIX _Scale = XMMatrixScaling(Scale.x, Scale.y, Scale.z);
	//XMMATRIX _Rotation = XMMatrixRotationQuaternion(XMVectorSet(Rotation.x, Rotation.y, Rotation.z, Rotation.w));

	XMMATRIX _Rotation = XMMatrixRotationX(Rotation.x) * XMMatrixRotationY(Rotation.y) * XMMatrixRotationZ(Rotation.z);

	XMMATRIX _Translation = XMMatrixTranslation(Position.x, Position.y,Position.z);

	return _Scale * _Rotation * _Translation;
}