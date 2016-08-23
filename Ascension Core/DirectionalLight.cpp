#include "DirectionalLight.h"



DirectionalLight::DirectionalLight()
{
}


DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::SetDirection(Vector3f dir)
{
	Direction = dir;
}

void DirectionalLight::SetIntensity(float intensity)
{
	Intensity = intensity;
}

void DirectionalLight::SetColor(signed char r, signed char g, signed char b)
{
	Color.x = r;
	Color.y = g;
	Color.z = b;
}

Vector3f DirectionalLight::GetDirection()
{
	return Direction;
}

float DirectionalLight::GetIntensity()
{
	return Intensity;
}

Vector3f DirectionalLight::GetColor()
{
	return Color;
}
