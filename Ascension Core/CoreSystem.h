#pragma once

#include "EngineSystem.h"
#include "Pool.h"
#include "Camera.h"

#define MAX_CAMERA_AMOUNT 32

class CoreSystem : public EngineSystem
{
public:
	Pool<Camera, MAX_CAMERA_AMOUNT> cameras;

	CoreSystem();
	~CoreSystem();

	void Update(float deltaTime);

	Handle<Component> GetCamera(Handle<GameObject> parentObject);

	template<typename... Args>
	inline void RemoveCamera(ComponentHandle cHandle, Args... args);

	static Handle<EngineSystem> GetHandle();
};


template<typename ...Args>
inline void CoreSystem::RemoveCamera(ComponentHandle cHandle, Args ...args)
{
	cameras.RemoveItem(Handle<Camera>(cHandle.CompHandle.GetIndex()), args...);
}
