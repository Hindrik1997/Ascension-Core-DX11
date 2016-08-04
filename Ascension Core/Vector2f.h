//
// Created by Hindrik Stegenga on 7/18/16.
//

#ifndef ASCENSION_CORE_VECTOR2F_H
#define ASCENSION_CORE_VECTOR2F_H

#include <cmath>

class Vector2f
{
public:
    float x;
    float y;

    Vector2f();
    Vector2f(float X, float Y);
    Vector2f(const Vector2f& Source);

    Vector2f& operator=(const Vector2f& Source);

    bool operator ==(const Vector2f& Rh);
    bool operator !=(const Vector2f& Rh);

    Vector2f operator-() const;

    Vector2f operator+(const Vector2f& Rh) const;
    Vector2f operator-(const Vector2f& Rh) const;

    Vector2f operator * (const float k) const;
    Vector2f operator / (const float k) const;

    Vector2f& operator += (const Vector2f& Rh);
    Vector2f& operator -= (const Vector2f& Rh);
    Vector2f& operator *= (const float k);
    Vector2f& operator /= (const float k);

    //Retourneert het dot product van de vectoren!
    float operator* (const Vector2f& Rh) const;


    //Maakt de vector (0,0)
    inline void Zero();
    //Maakt een unit vector van de vector.
    void Normalize();
    //Haalt de Magnitude(Lengte) van de vector op. (Zie GetMagnitude())
    inline float Magnitude();
};

//INLINE NON MEMBERS

inline float GetMagnitude(const Vector2f& Vector)
{
    return std::sqrt(Vector.x * Vector.x + Vector.y * Vector.y);
}

//INLINE MEMBERS

inline float Vector2f::Magnitude()
{
    return GetMagnitude(*this);
}

inline void Vector2f::Zero()
{
    x = 0.0f;
    y = 0.0f;
}


#endif //ASCENSION_CORE_VECTOR2F_H
