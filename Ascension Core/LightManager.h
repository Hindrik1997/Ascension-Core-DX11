#pragma once
#include "Vector3f.h"
#include "Handle.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Pool.h"

#define DIR_LIGHT_WORLD_LIMIT 8
#define POINT_LIGHT_WORLD_LIMIT 32767
#define LIGHT_CULL_RANGE 100

typedef Pool<DirectionalLight, DIR_LIGHT_WORLD_LIMIT> DLPool;
typedef Pool<PointLight, POINT_LIGHT_WORLD_LIMIT> PLPool;

class LightManager
{
public:
	LightManager();
	~LightManager();

private:
	float AmbientIntensity = 37.75f;
	Vector3f AmbientColor = Vector3f(255.0f, 255.0f, 255.0f);	
public:
	//Intensity in range of 0-255
	void SetAmbientIntensity(signed char intensity);
	float GetAmbientIntensity();

	//Color in range of 0-255
	void SetAmbientColor(signed char r, signed char g, signed char b);
	Vector3f GetAmbientColor();

	//Maximum of POINT_LIGHT_LIMIT lights can be put into the scene. If you exceed this limit, this function will throw an exception
	Handle<PointLight> AddPointLight();

	const Pool<DirectionalLight, DIR_LIGHT_WORLD_LIMIT>& GetDirectionalLightsList();
	const Pool<PointLight, POINT_LIGHT_WORLD_LIMIT>& GetPointLightsList();

	//Removes point light, invalidates the handle.
	void RemovePointLight(Handle<PointLight> light);

	//Maximum of 8 directional lights can be added. If you exceed this limit, this function will throw an exception
	Handle<DirectionalLight> AddDirectionalLight();

	//Removes directional light, invalidates the handle.
	void RemoveDirectionalLight(Handle<DirectionalLight> light);
private:
	PLPool PntLightPool;
	DLPool DirLightPool;
};

