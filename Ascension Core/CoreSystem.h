#pragma once

#include "EngineSystem.h"
#include "Pool.h"
#include "Camera.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Limits.h"

typedef Pool<Camera, MAX_CAMERA_AMOUNT> CLPool;
typedef Pool<DirectionalLight, DIR_LIGHT_WORLD_LIMIT> DLPool;
typedef Pool<PointLight, POINT_LIGHT_WORLD_LIMIT> PLPool;

class CoreSystem : public EngineSystem
{
private:
	float AmbientIntensity = 45.9f;
	Vector3f AmbientColor = Vector3f(255.0f, 255.0f, 255.0f);


	PLPool PntLightPool;
	DLPool DirLightPool;
public:
	CLPool cameras;
public:
	CoreSystem();
	~CoreSystem();

	void Update(float deltaTime);

	template<typename T>
	T& GetFromStorage(int index);


	//Camera
	Handle<Component> GetCamera(Handle<GameObject> parentObject);

	template<typename... Args>
	inline void RemoveCamera(ComponentHandle cHandle, Args... args);

	//Point light
	Handle<Component> GetPointLight(Handle<GameObject> parentObject);

	template<typename... Args>
	inline void RemovePointLight(ComponentHandle cHandle, Args... args);

	//Directional light
	Handle<Component> GetDirectionalLight(Handle<GameObject> parentObject);

	template<typename... Args>
	inline void RemoveDirectionalLight(ComponentHandle cHandle, Args... args);

	//Spot light
	Handle<Component> GetSpotLight(Handle<GameObject> parentObject);

	template<typename... Args>
	inline void RemoveSpotLight(ComponentHandle cHandle, Args... args);


	//Intensity in range of 0-255
	void SetAmbientIntensity(signed char intensity);
	float GetAmbientIntensity();

	//Color in range of 0-255
	void SetAmbientColor(signed char r, signed char g, signed char b);
	Vector3f GetAmbientColor();

	const Pool<DirectionalLight, DIR_LIGHT_WORLD_LIMIT>& GetDirectionalLightsList();
	const Pool<PointLight, POINT_LIGHT_WORLD_LIMIT>& GetPointLightsList();

	static Handle<EngineSystem> GetHandle();
};

template<typename T>
inline T& CoreSystem::GetFromStorage(int index)
{
	throw "Please specialize the appropriate type!";
}

//Specializations
template<>
inline Camera& CoreSystem::GetFromStorage(int index) 
{
	return cameras[index];
};

template<>
inline PointLight& CoreSystem::GetFromStorage(int index)
{
	return PntLightPool[index];
};

template<>
inline DirectionalLight& CoreSystem::GetFromStorage(int index)
{
	return DirLightPool[index];
};

template<typename ...Args>
inline void CoreSystem::RemoveCamera(ComponentHandle cHandle, Args ...args)
{
	cameras.RemoveItem(Handle<Camera>(cHandle.GetCompHandle().GetIndex()), args...);
}

template<typename ...Args>
inline void CoreSystem::RemovePointLight(ComponentHandle cHandle, Args ...args)
{
	PntLightPool.RemoveItem(Handle<PointLight>(cHandle.GetCompHandle().GetIndex()), args...);
}

template<typename ...Args>
inline void CoreSystem::RemoveDirectionalLight(ComponentHandle cHandle, Args ...args)
{
	DirLightPool.RemoveItem(Handle<DirectionalLight>(cHandle.GetCompHandle().GetIndex()), args...);
}

template<typename ...Args>
inline void CoreSystem::RemoveSpotLight(ComponentHandle cHandle, Args ...args)
{
	//PntLightPool.RemoveItem(Handle<PointLight>(cHandle.GetCompHandle().GetIndex()), args...);
}