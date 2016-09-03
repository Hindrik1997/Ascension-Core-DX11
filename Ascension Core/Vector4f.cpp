//
// Created by Hindrik Stegenga on 7/18/16.
//

#include "Vector4f.h"

Vector4f::Vector4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}

Vector4f::Vector4f(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W)
{
}

Vector4f::Vector4f(const Vector4f& Source) : x(Source.x), y(Source.y), z(Source.z), w(Source.w)
{
}

Vector4f& Vector4f::operator=(const Vector4f & Source)
{
    x = Source.x; y = Source.y; z = Source.y; w = Source.w;
    return *this;
}

bool Vector4f::operator==(const Vector4f & Rh)
{
    return x == Rh.x && y == Rh.y && z == Rh.z && w == Rh.w;
}

bool Vector4f::operator!=(const Vector4f & Rh)
{
    return !operator==(Rh);
}

Vector4f Vector4f::operator- () const
{
    return Vector4f(-x, -y, -z, -w);
}

Vector4f Vector4f::operator+(const Vector4f& Rh) const
{
    return Vector4f(x + Rh.x, y + Rh.y, z + Rh.z, w + Rh.w);
}

Vector4f Vector4f::operator-(const Vector4f& Rh) const
{
    return Vector4f(x - Rh.x, y - Rh.y, z - Rh.z, w - Rh.w);
}

Vector4f Vector4f::operator*(const float k) const
{
    return Vector4f(x*k, y*k, z*k, w*k);
}

Vector4f Vector4f::operator/(const float k) const
{
    float oneOverK = 1.0f / k;
    return Vector4f(x*oneOverK, y*oneOverK, z*oneOverK, w*oneOverK);
}

Vector4f& Vector4f::operator+=(const Vector4f& Rh)
{
    x += Rh.x; y += Rh.y; z += Rh.z; w += Rh.w; return *this;
}

Vector4f& Vector4f::operator-=(const Vector4f& Rh)
{
    x -= Rh.x; y -= Rh.y; z -= Rh.z; w -= Rh.w;  return *this;
}

Vector4f& Vector4f::operator*=(const float k)
{
    x *= k; y *= k; z *= k; w *= k; return *this;
}

Vector4f& Vector4f::operator/=(const float k)
{
    float OneOverK = 1.0f / k;
    x *= OneOverK; y *= OneOverK; z *= OneOverK; w *= OneOverK; return *this;
}

float Vector4f::operator*(const Vector4f& Rh) const
{
    return x*Rh.x + y*Rh.y + z*Rh.z + w*Rh.w;
}

void Vector4f::Normalize()
{
    float MagnitudeSquare = x*x + y*y + z*z + w*w;
    float OneOverMagnitude = 1.0f / MagnitudeSquare;
    x *= OneOverMagnitude;
    y *= OneOverMagnitude;
    z *= OneOverMagnitude;
    w *= OneOverMagnitude;
}
