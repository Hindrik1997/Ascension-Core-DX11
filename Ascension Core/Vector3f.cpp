//
// Created by Hindrik Stegenga on 7/18/16.
//

#include "Vector3f.h"

Vector3f::Vector3f() : x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3f::Vector3f(float X, float Y, float Z) : x(X), y(Y), z(Z)
{
}

Vector3f::Vector3f(const Vector3f& Source) : x(Source.x), y(Source.y), z(Source.z)
{
}

Vector3f& Vector3f::operator=(const Vector3f & Source)
{
    x = Source.x; y = Source.y; z = Source.z;
    return *this;
}

bool Vector3f::operator==(const Vector3f & Rh)
{
    return x == Rh.x && y == Rh.y && z == Rh.z;
}

bool Vector3f::operator!=(const Vector3f & Rh)
{
    return !operator==(Rh);
}

Vector3f Vector3f::operator- () const
{
    return Vector3f(-x, -y, -z);
}

Vector3f Vector3f::operator+(const Vector3f& Rh) const
{
    return Vector3f(x + Rh.x, y + Rh.y, z + Rh.z);
}

Vector3f Vector3f::operator-(const Vector3f& Rh) const
{
    return Vector3f(x - Rh.x, y - Rh.y, z - Rh.z);
}

Vector3f Vector3f::operator*(const float k) const
{
    return Vector3f(x*k, y*k, z*k);
}

Vector3f Vector3f::operator/(const float k) const
{
    float oneOverK = 1.0f / k;
    return Vector3f(x*oneOverK, y*oneOverK, z*oneOverK);
}

Vector3f& Vector3f::operator+=(const Vector3f& Rh)
{
    x += Rh.x; y += Rh.y; z += Rh.z; return *this;
}

Vector3f& Vector3f::operator-=(const Vector3f& Rh)
{
    x -= Rh.x; y -= Rh.y; z -= Rh.z; return *this;
}

Vector3f& Vector3f::operator*=(const float k)
{
    x *= k; y *= k; z *= k; return *this;
}

Vector3f& Vector3f::operator/=(const float k)
{
    float OneOverK = 1.0f / k;
    x *= OneOverK; y *= OneOverK; z *= OneOverK; return *this;
}

float Vector3f::operator*(const Vector3f& Rh) const
{
    return x*Rh.x + y*Rh.y + z*Rh.z;
}

void Vector3f::Normalize()
{
    float MagnitudeSquare = x*x + y*y + z*z;
    float OneOverMagnitude = 1.0f / MagnitudeSquare;
    x *= OneOverMagnitude;
    y *= OneOverMagnitude;
    z *= OneOverMagnitude;
}
