#include "PointLight.h"



PointLight::PointLight()
{
}


PointLight::~PointLight()
{
}

void PointLight::SetIntensity(float intensity)
{
	Intensity = intensity;
}

void PointLight::SetColor(float r, float g, float b)
{
	Color.x = r;
	Color.y = g;
	Color.z = b;
}

float PointLight::GetIntensity()
{
	return Intensity;
}

Vector3f PointLight::GetColor()
{
	return Color;
}

void PointLight::SetPosition(Vector3f v)
{
	Position = v;
}

Vector3f PointLight::GetPosition()
{
	return Position;
}

void PointLight::SetRadius(float r)
{
	Radius = r;
}

float PointLight::GetRadius()
{
	return Radius;
}
