#include "LightManager.h"


LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}

void LightManager::SetAmbientIntensity(signed char intensity)
{
	AmbientIntensity = intensity;
}

float LightManager::GetAmbientIntensity()
{
	return AmbientIntensity;
}

void LightManager::SetAmbientColor(signed char r, signed char g, signed char b)
{
	AmbientColor.x = r;
	AmbientColor.y = g;
	AmbientColor.z = b;
}

Vector3f LightManager::GetAmbientColor()
{
	return AmbientColor;
}

Handle<PointLight> LightManager::AddPointLight()
{
	return PntLightPool.GetNewItem();
}

const Pool<DirectionalLight, DIR_LIGHT_WORLD_LIMIT>& LightManager::GetDirectionalLightsList()
{
	return DirLightPool;
}

const Pool<PointLight, POINT_LIGHT_WORLD_LIMIT>& LightManager::GetPointLightsList()
{
	return PntLightPool;
}

void LightManager::RemovePointLight(Handle<PointLight> light)
{
	PntLightPool.RemoveItem(light);
}

Handle<DirectionalLight> LightManager::AddDirectionalLight()
{
	return DirLightPool.GetNewItem();
}

void LightManager::RemoveDirectionalLight(Handle<DirectionalLight> light)
{
	DirLightPool.RemoveItem(light);
}
