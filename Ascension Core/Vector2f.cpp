//
// Created by Hindrik Stegenga on 7/18/16.
//

#include "Vector2f.h"


Vector2f::Vector2f() : x(0.0f), y(0.0f)
{
}

Vector2f::Vector2f(float X, float Y) : x(X), y(Y)
{
}

Vector2f::Vector2f(const Vector2f& Source) : x(Source.x), y(Source.y)
{
}

Vector2f& Vector2f::operator=(const Vector2f & Source)
{
    x = Source.x; y = Source.y;
    return *this;
}

bool Vector2f::operator==(const Vector2f & Rh)
{
    return x == Rh.x && y == Rh.y;
}

bool Vector2f::operator!=(const Vector2f & Rh)
{
    return !operator==(Rh);
}

Vector2f Vector2f::operator- () const
{
    return Vector2f(-x, -y);
}

Vector2f Vector2f::operator+(const Vector2f& Rh) const
{
    return Vector2f(x + Rh.x, y + Rh.y);
}

Vector2f Vector2f::operator-(const Vector2f& Rh) const
{
    return Vector2f(x - Rh.x, y - Rh.y);
}

Vector2f Vector2f::operator*(const float k) const
{
    return Vector2f(x*k, y*k);
}

Vector2f Vector2f::operator/(const float k) const
{
    float oneOverK = 1.0f / k;
    return Vector2f(x*oneOverK, y*oneOverK);
}

Vector2f& Vector2f::operator+=(const Vector2f& Rh)
{
    x += Rh.x; y += Rh.y; return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& Rh)
{
    x -= Rh.x; y -= Rh.y; return *this;
}

Vector2f& Vector2f::operator*=(const float k)
{
    x *= k; y *= k;  return *this;
}

Vector2f& Vector2f::operator/=(const float k)
{
    float OneOverK = 1.0f / k;
    x *= OneOverK; y *= OneOverK; return *this;
}

float Vector2f::operator*(const Vector2f& Rh) const
{
    return x*Rh.x + y*Rh.y;
}

void Vector2f::Normalize()
{
    float MagnitudeSquare = x*x + y*y;
    float OneOverMagnitude = 1.0f / MagnitudeSquare;
    x *= OneOverMagnitude;
    y *= OneOverMagnitude;
}
