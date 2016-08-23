#pragma once
#include "Vector3f.h"

class DirectionalLight
{
private:
	Vector3f Color = Vector3f(255.0f, 255.0f, 255.0f);
	float Intensity = 255.0f;
	Vector3f Direction = Vector3f(0.0f, 0.0f, -1.0f);
public:
	DirectionalLight();
	~DirectionalLight();

	void SetDirection(Vector3f dir);
	void SetIntensity(float intensity);
	void SetColor(signed char r, signed char g, signed char b);

	Vector3f GetDirection();
	float GetIntensity();
	Vector3f GetColor();
};

