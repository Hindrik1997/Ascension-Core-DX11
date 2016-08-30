#pragma once
#include "Vector3f.h"

class PointLight
{
private:
	Vector3f Position = Vector3f(10.0f, 10.0f, 10.0f);
	Vector3f Color = Vector3f(255.0f, 255.0f, 255.0f);
	float Intensity = 1.0f;
	Vector3f Direction = Vector3f(0.0f, 0.0f, -1.0f);

public:
	PointLight();
	~PointLight();

	//Direction vector
	void SetDirection(Vector3f dir);

	//As float value from 0 to 1 (Higher is possible, but not recommended, unless you implement HDR :D)
	void SetIntensity(float intensity);

	//As rgb value from 0 to 255
	void SetColor(float r, float g, float b);

	Vector3f GetDirection();
	float GetIntensity();
	Vector3f GetColor();

	void SetPosition(Vector3f v);
	Vector3f GetPosition();

};

