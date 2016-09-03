#include "DirectionalLight.h"
#include "CoreSystem.h"
#include "Engine.h"

Handle<EngineSystem> DirectionalLight::sysHandle;

DirectionalLight::DirectionalLight(Handle<GameObject> parentObject) : Component(parentObject)
{
}


DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::SetDirection(Vector3f dir)
{
	Direction = dir;
}



void DirectionalLight::SetColor(float r, float g, float b)
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

void DirectionalLight::SetIntensity(float intensity)
{
	Intensity = intensity;
}

Vector3f DirectionalLight::GetColor()
{
	return Color;
}

Handle<EngineSystem> DirectionalLight::GetSystemHandle()
{
	return (sysHandle.GetIndex() == -1) ? CoreSystem::GetHandle() : sysHandle;
}

//template implementations
template<typename... ResetArgs>
Handle<Component> DirectionalLight::AddComponent(Handle<GameObject> parentObject, ResetArgs... arguments)
{
	return static_cast<CoreSystem*>(&Engine::MainInstance().SystemsManager[GetSystemHandle().GetIndex()])->GetDirectionalLight(parentObject, arguments...);
}

template<typename ...ResetArgs>
void DirectionalLight::RemoveComponent(ComponentHandle cHandle, ResetArgs ...arguments)
{
	static_cast<CoreSystem*>(&Engine::MainInstance().SystemsManager[GetSystemHandle().GetIndex()])->RemoveDirectionalLight(cHandle, arguments...);
}

//explicit instantiations
template Handle<Component> DirectionalLight::AddComponent(Handle<GameObject> parentObject);
template void DirectionalLight::RemoveComponent(ComponentHandle cHandle);

CoreSystem& DirectionalLight::ConvertToParentSystemType(EngineSystem& system)
{
	return static_cast<CoreSystem&>(system);
}