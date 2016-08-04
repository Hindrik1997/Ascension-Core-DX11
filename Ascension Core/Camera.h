#pragma once

#include "EngineSystem.h"
#include "Component.h"
#include "ComponentHandle.h"
#include "Vector3f.h"

class Engine;

class Camera : public Component
{
private:
	Vector3f LookAtVector;
	Vector3f UpVector;
public:
	Vector3f GetCamPosition();
	inline Vector3f GetUpVector();
	inline Vector3f GetLookAtVector();
public:
	Camera(Handle<GameObject> parentObject);
	~Camera();

	template<typename... ResetArgs>
	static Handle<Component> AddComponent(Handle<GameObject> parentObject, ResetArgs... arguments);

	template<typename... ResetArgs>
	static void RemoveComponent(ComponentHandle cHandle, ResetArgs... arguments);

	static Handle<EngineSystem> GetSystemHandle();
private:
	static Handle<EngineSystem> sysHandle;
};

inline Vector3f Camera::GetUpVector()
{
	return UpVector;
}

inline Vector3f Camera::GetLookAtVector()
{
	return LookAtVector;
}