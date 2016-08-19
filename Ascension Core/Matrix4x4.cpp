#include "Matrix4x4.h"


const float PI = 3.1415927f;

Matrix4x4::Matrix4x4()
{
	ClearMatrix();
}


Matrix4x4::~Matrix4x4()
{
}

void Matrix4x4::ClearMatrix()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			data[i][j] = 0.0f;
		}
	}
}

void Matrix4x4::SetIdentity()
{
	ClearMatrix();
	data[0][0] = 1.0f;
	data[1][1] = 1.0f;
	data[2][2] = 1.0f;
	data[3][3] = 1.0f;
}

void Matrix4x4::SetTranslation(float x, float y, float z)
{
	SetIdentity();
	data[0][3] = x;
	data[1][3] = y;
	data[2][3] = z;
}

void Matrix4x4::SetTranslation(Vector3f vec)
{
	SetIdentity();

	data[3][0] = vec.x;
	data[3][1] = vec.y;
	data[3][2] = vec.z;
}

void Matrix4x4::SetRotation(float x, float y, float z)
{
	SetIdentity();

	Matrix4x4 result, rx, ry, rz;


	result.SetIdentity();
	rx.SetIdentity();
	ry.SetIdentity();
	rz.SetIdentity();


	x = ConvertToRadians(x);
	y = ConvertToRadians(y);
	z = ConvertToRadians(z);

	rz.Set(0, 0, cos(z)); rz.Set(0, 1, - sin(z)); 
	rz.Set(1, 0, sin(z)); rz.Set(1, 1,   cos(z));

	rx.Set(1, 1, cos(x)); rx.Set(1, 2, - sin(x));
	rx.Set(2, 1, sin(x)); rx.Set(2, 2,   cos(x));

	ry.Set(0, 0, cos(y)); ry.Set(0, 2, - sin(y));
	ry.Set(2, 0, sin(y)); ry.Set(2, 2,   cos(y));

	result = Multiply(rz, Multiply(ry,rx));
	result.Transpose();
	CopyMatrixAtoB(result, *this);
}

void Matrix4x4::SetRotation(Vector3f vec)
{
	SetRotation(vec.x, vec.y, vec.z);
}

void Matrix4x4::SetScale(float x, float y, float z)
{
	SetIdentity();

	data[0][0] = x;
	data[1][1] = y;
	data[2][2] = z;
	data[3][3] = 1.0f;
}

void Matrix4x4::SetScale(Vector3f vec)
{
	SetIdentity();

	data[0][0] = vec.x;
	data[1][1] = vec.y;
	data[2][2] = vec.z;
	data[3][3] = 1.0f;
}

Matrix4x4 Matrix4x4::Multiply(Matrix4x4 A, Matrix4x4 B)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result.Set(i, j, A.Get(i, 0) * B.Get(0, j) + A.Get(i,1) * B.Get(1,j) + A.Get(i, 2) * B.Get(2, j) + A.Get(i, 3) * B.Get(3, j));
		}
	}
	return result;
}

Vector4f Matrix4x4::Transform(Vector4f vec, Matrix4x4 mat)
{
	Vector4f result;

	result.x = vec.x * mat.Get(0, 0) + vec.y * mat.Get(1, 0) + vec.z * mat.Get(2, 0) + vec.w * mat.Get(3, 0);
	result.y = vec.x * mat.Get(0, 1) + vec.y * mat.Get(1, 1) + vec.z * mat.Get(2, 1) + vec.w * mat.Get(3, 1);
	result.z = vec.x * mat.Get(0, 2) + vec.y * mat.Get(1, 2) + vec.z * mat.Get(2, 2) + vec.w * mat.Get(3, 2);
	result.w = vec.w * mat.Get(0, 3) + vec.y * mat.Get(1, 3) + vec.z * mat.Get(2, 3) + vec.w * mat.Get(3, 3);

	return result;
}

float Matrix4x4::Get(int i, int j)
{
	return data[i][j];
}

void Matrix4x4::Set(int i, int j, float val)
{
	data[i][j] = val;
}

void Matrix4x4::Transpose()
{
	Matrix4x4 transpose;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			transpose.Set(j,i, Get(i,j));
		}
	}

	CopyMatrixAtoB(transpose, *this);
}

float ConvertToRadians(float degrees)
{
	return (degrees * PI) / 180.0f;
}

float ConvertToDegrees(float radians)
{
	return (radians * 180) / PI;
}

void CopyMatrixAtoB(Matrix4x4& A, Matrix4x4& B)
{
	for (int i = 0; i < 4; ++i) 
	{
		for (int j = 0; j < 4; ++j)
		{
			B.Set(i,j, A.Get(i,j));
		}
	};
}
