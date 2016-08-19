#pragma once
#include "Vector3f.h"
#include "Vector4f.h"

class Matrix4x4
{
private:
	float data[4][4];
public:
	Matrix4x4();
	~Matrix4x4();

	void ClearMatrix();
	void SetIdentity();

	void SetTranslation(float x, float y, float z);
	void SetTranslation(Vector3f vec);

	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3f vec);

	void SetScale(float x, float y, float z);
	void SetScale(Vector3f vec);
	
	static Matrix4x4 Multiply(Matrix4x4 A, Matrix4x4 B);
	static Vector4f	 Transform(Vector4f vec, Matrix4x4 mat);

	float Get(int i, int j);
	void  Set(int i, int j, float val);

	void Transpose();
};

float ConvertToRadians(float val);
float ConvertToDegrees(float val);
void  CopyMatrixAtoB(Matrix4x4& A, Matrix4x4& B);