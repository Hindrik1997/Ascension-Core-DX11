#pragma once
#include "Vector3f.h"
#include "Component.h"
#include "ComponentHandle.h"

class CoreSystem;

class DirectionalLight : public Component
{
private:
	Vector3f Color = Vector3f(255.0f, 255.0f, 255.0f);
	float Intensity = 1.0f;
	Vector3f Direction = Vector3f(0.0f, 0.0f, -1.0f);
public:
	DirectionalLight(Handle<GameObject> parentObject);
	~DirectionalLight();

	//Direction vector
	void SetDirection(Vector3f dir);

	//As float value from 0 to 1 (Higher is possible!)
	void SetIntensity(float intensity);

	//As rgb value from 0 to 255
	void SetColor(float r, float g, float b);

	Vector3f GetDirection();
	float GetIntensity();
	Vector3f GetColor();
public:
	template<typename... ResetArgs>
	static Handle<Component> AddComponent(Handle<GameObject> parentObject, ResetArgs... arguments);

	template<typename... ResetArgs>
	static void RemoveComponent(ComponentHandle cHandle, ResetArgs... arguments);

	static CoreSystem& ConvertToParentSystemType(EngineSystem& system);
	static Handle<EngineSystem> GetSystemHandle();
private:
	static Handle<EngineSystem> sysHandle;
};