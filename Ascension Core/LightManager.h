#pragma once
#include "Vector3f.h"


class LightManager
{
public:
	LightManager();
	~LightManager();

private:
	float AmbientIntensity = 0.4f;
	Vector3f AmbientColor = Vector3f(1.0f, 1.0f, 1.0f);


	
public:
	void SetAmbientIntensity(float intensity);
	float GetAmbientIntensity();

	void SetAmbientColor(Vector3f color);
	Vector3f GetAmbientColor();
};

