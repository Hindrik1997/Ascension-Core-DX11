#include "PointLight.h"



PointLight::PointLight()
{
}


PointLight::~PointLight()
{
}

void PointLight::SetDirection(Vector3f dir)
{
}

void PointLight::SetIntensity(float intensity)
{
}

void PointLight::SetColor(float r, float g, float b)
{
}

Vector3f PointLight::GetDirection()
{
	return Vector3f();
}

float PointLight::GetIntensity()
{
	return 0.0f;
}

Vector3f PointLight::GetColor()
{
	return Vector3f();
}

void PointLight::SetPosition(Vector3f v)
{
	Position = v;
}

Vector3f PointLight::GetPosition()
{
	return Position;
}
