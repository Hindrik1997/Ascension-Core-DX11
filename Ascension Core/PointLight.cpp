#include "PointLight.h"
#include "CoreSystem.h"
#include "Engine.h"

Handle<EngineSystem> PointLight::sysHandle;

PointLight::PointLight(Handle<GameObject> parentObject) : Component(parentObject)
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

Handle<EngineSystem> PointLight::GetSystemHandle()
{
	return (sysHandle.GetIndex() == -1) ? CoreSystem::GetHandle() : sysHandle;
}

CoreSystem& PointLight::ConvertToParentSystemType(EngineSystem& system)
{
	return static_cast<CoreSystem&>(system);
}

//template implementations
template<typename... ResetArgs>
Handle<Component> PointLight::AddComponent(Handle<GameObject> parentObject, ResetArgs... arguments)
{
	return static_cast<CoreSystem*>(&Engine::MainInstance().SystemsManager[GetSystemHandle().GetIndex()])->GetPointLight(parentObject, arguments...);
}

template<typename ...ResetArgs>
void PointLight::RemoveComponent(ComponentHandle cHandle, ResetArgs ...arguments)
{
	static_cast<CoreSystem*>(&Engine::MainInstance().SystemsManager[GetSystemHandle().GetIndex()])->RemovePointLight(cHandle, arguments...);
}

//explicit instantiations
template Handle<Component> PointLight::AddComponent(Handle<GameObject> parentObject);
template void PointLight::RemoveComponent(ComponentHandle cHandle);