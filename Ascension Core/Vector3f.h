//
// Created by Hindrik Stegenga on 7/18/16.
//

#ifndef ASCENSION_CORE_VECTOR3F_H
#define ASCENSION_CORE_VECTOR3F_H

#include <cmath>

class Vector3f
{
public:
    float x;
    float y;
    float z;

    Vector3f();
    Vector3f(float X, float Y, float Z);
    Vector3f(const Vector3f& Source);

    Vector3f& operator=(const Vector3f& Source);

    bool operator ==(const Vector3f& Rh);
    bool operator !=(const Vector3f& Rh);

    Vector3f operator-() const;

    Vector3f operator+(const Vector3f& Rh) const;
    Vector3f operator-(const Vector3f& Rh) const;

    Vector3f operator * (const float k) const;
    Vector3f operator / (const float k) const;

    Vector3f& operator += (const Vector3f& Rh);
    Vector3f& operator -= (const Vector3f& Rh);
    Vector3f& operator *= (const float k);
    Vector3f& operator /= (const float k);

    //Retourneert het dot product van de vectoren!
    float operator* (const Vector3f& Rh) const;


    //Maakt de vector (0,0,0)
    inline void Zero();
    //Maakt een unit vector van de vector.
    void Normalize();
    //Haalt de Magnitude(Lengte) van de vector op. (Zie GetMagnitude())
    inline float Magnitude();
};

//INLINE NON MEMBERS

inline float GetMagnitude(const Vector3f& Vector)
{
    return std::sqrt(Vector.x * Vector.x + Vector.y * Vector.y + Vector.z * Vector.z);
}

inline Vector3f CrossProduct(const Vector3f& VectorA, const Vector3f& VectorB)
{
    return Vector3f(VectorA.y * VectorB.z - VectorA.z *VectorB.y, VectorA.z*VectorB.x - VectorA.x*VectorB.z, VectorA.x*VectorB.y - VectorA.y * VectorB.x);
}

//INLINE MEMBERS

inline float Vector3f::Magnitude()
{
    return GetMagnitude(*this);
}

inline void Vector3f::Zero()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}


#endif //ASCENSION_CORE_VECTOR3F_H
