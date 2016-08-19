#include "Quaternion.h"
#include <cmath>




Quaternion::Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
{
}

Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}


Quaternion::~Quaternion()
{
}

float Length(Quaternion quat)
{
	return sqrt(quat.x * quat.x + quat.y * quat.y +
		quat.z * quat.z + quat.w * quat.w);
}

Quaternion Normalize(Quaternion quat)
{
	float L = Length(quat);

	quat.x /= L;
	quat.y /= L;
	quat.z /= L;
	quat.w /= L;
	return quat;
}

Quaternion Conjugate(Quaternion quat)
{
	quat.x = -quat.x;
	quat.y = -quat.y;
	quat.z = -quat.z;
	return quat;
}

Quaternion Multiply(Quaternion A, Quaternion B)
{
	Quaternion C;

	C.x = A.w*B.x + A.x*B.w + A.y*B.z - A.z*B.y;
	C.y = A.w*B.y - A.x*B.z + A.y*B.w + A.z*B.x;
	C.z = A.w*B.z + A.x*B.y - A.y*B.x + A.z*B.w;
	C.w = A.w*B.w - A.x*B.x - A.y*B.y - A.z*B.z;
	return C;
}

Quaternion RotatePointOverAxis(float angle, Vector3f axis, Vector3f point)
{
	Quaternion puntQuaternion(point.x, point.y, point.z, 0.0f);
	Vector3f n = axis;
	n.Normalize();
	Quaternion rotatieQuaternion(n.x * sin(angle/2), n.y * sin(angle/2), n.z * sin(angle/2), cos(angle/2));
	Quaternion conjugateQuaternion = Conjugate(rotatieQuaternion);

	Quaternion result = Multiply(Multiply(rotatieQuaternion, puntQuaternion), conjugateQuaternion);
	return result;
}

