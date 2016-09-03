#include "CoreSystem.h"
#include "Engine.h"

CoreSystem::CoreSystem()
{
	
}

void CoreSystem::Update(float deltaTime)
{
}

Handle<Component> CoreSystem::GetCamera(Handle<GameObject> parentObject)
{
	return Handle<Component>(cameras.GetNewItem(parentObject).GetIndex());
}

Handle<Component> CoreSystem::GetPointLight(Handle<GameObject> parentObject)
{
	return Handle<Component>();
}

Handle<Component> CoreSystem::GetDirectionalLight(Handle<GameObject> parentObject)
{
	return Handle<Component>();
}

Handle<Component> CoreSystem::GetSpotLight(Handle<GameObject> parentObject)
{
	return Handle<Component>();
}

CoreSystem::~CoreSystem()
{
}

Handle<EngineSystem> CoreSystem::GetHandle()
{
	for (size_t i = 0; i < Engine::MainInstance().SystemsManager.GetSystems().size(); ++i)
	{
		if (typeid(CoreSystem) == typeid(*(Engine::MainInstance().SystemsManager.GetSystems())[i]))
		{
			return Handle<EngineSystem>(static_cast<int>(i));
		}
	}
	throw "System not found in engine!";
}

void CoreSystem::SetAmbientIntensity(signed char intensity)
{
	AmbientIntensity = intensity;
}

float CoreSystem::GetAmbientIntensity()
{
	return AmbientIntensity;
}

void CoreSystem::SetAmbientColor(signed char r, signed char g, signed char b)
{
	AmbientColor.x = r;
	AmbientColor.y = g;
	AmbientColor.z = b;
}

Vector3f CoreSystem::GetAmbientColor()
{
	return AmbientColor;
}

const Pool<DirectionalLight, DIR_LIGHT_WORLD_LIMIT>& CoreSystem::GetDirectionalLightsList()
{
	return DirLightPool;
}

const Pool<PointLight, POINT_LIGHT_WORLD_LIMIT>& CoreSystem::GetPointLightsList()
{
	return PntLightPool;
}

