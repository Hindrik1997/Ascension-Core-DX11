#pragma once
#include "Vector3f.h"
#include "Component.h"
#include "ComponentHandle.h"

class CoreSystem;

class PointLight : public Component
{
private:
	Vector3f Position = Vector3f(0.0f, 1.0f, 0.0f);
	Vector3f Color = Vector3f(255.0f, 0,0);
	float Intensity = 1.0f;
	float Radius = 2.0f;
public:
	PointLight(Handle<GameObject> parentObject);
	~PointLight();

	//As float value from 0 to 1 (Higher is possible, but not recommended, unless you implement HDR :D)
	void SetIntensity(float intensity);

	//As rgb value from 0 to 255
	void SetColor(float r, float g, float b);

	float GetIntensity();
	Vector3f GetColor();

	void SetPosition(Vector3f v);
	Vector3f GetPosition();

	void SetRadius(float r);
	float GetRadius();
public:
	template<typename... ResetArgs>
	static Handle<Component> AddComponent(Handle<GameObject> parentObject, ResetArgs... arguments);

	template<typename... ResetArgs>
	static void RemoveComponent(ComponentHandle cHandle, ResetArgs... arguments);

	static Handle<EngineSystem> GetSystemHandle();

	static CoreSystem& ConvertToParentSystemType(EngineSystem& system);
private:
	static Handle<EngineSystem> sysHandle;
};

