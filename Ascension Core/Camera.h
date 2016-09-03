#pragma once

#include "EngineSystem.h"
#include "Component.h"
#include "ComponentHandle.h"
#include "Vector3f.h"
#include "Transform.h"

class Engine;

class Camera : public Component
{
public:
	Vector3f Up;
	Vector3f Forward;
	
public:
	Vector3f GetCamPosition();
	void SetCamPosition(Vector3f pos);

	Vector3f GetRightVector();
	Vector3f GetLeftVector();
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
