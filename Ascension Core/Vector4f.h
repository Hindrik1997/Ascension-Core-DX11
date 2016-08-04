//
// Created by Hindrik Stegenga on 7/18/16.
//

#ifndef ASCENSION_CORE_VECTOR4F_H
#define ASCENSION_CORE_VECTOR4F_H

#include <cmath>

class Vector4f
{
public:
    float x;
    float y;
    float z;
    float w;

    Vector4f();
    Vector4f(float X, float Y, float Z, float W);
    Vector4f(const Vector4f& Source);

    Vector4f& operator=(const Vector4f& Source);

    bool operator ==(const Vector4f& Rh);
    bool operator !=(const Vector4f& Rh);

    Vector4f operator-() const;

    Vector4f operator+(const Vector4f& Rh) const;
    Vector4f operator-(const Vector4f& Rh) const;

    Vector4f operator * (const float k) const;
    Vector4f operator / (const float k) const;

    Vector4f& operator += (const Vector4f& Rh);
    Vector4f& operator -= (const Vector4f& Rh);
    Vector4f& operator *= (const float k);
    Vector4f& operator /= (const float k);

    //Retourneert het dot product van de vectoren!
    float operator* (const Vector4f& Rh) const;


    //Maakt de vector (0,0,0)
    inline void Zero();
    //Maakt een unit vector van de vector.
    void Normalize();
    //Haalt de Magnitude(Lengte) van de vector op. (Zie GetMagnitude())
    inline float Magnitude();
};

//INLINE NON MEMBERS

inline float GetMagnitude(const Vector4f& Vector)
{
    return std::sqrt(Vector.x * Vector.x + Vector.y * Vector.y + Vector.z * Vector.z + Vector.w * Vector.w);
}

//INLINE MEMBERS

inline float Vector4f::Magnitude()
{
    return GetMagnitude(*this);
}

inline void Vector4f::Zero()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}


#endif //ASCENSION_CORE_VECTOR4F_H
