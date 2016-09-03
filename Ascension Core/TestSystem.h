//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_TESTSYSTEM_H
#define ASCENSION_CORE_TESTSYSTEM_H

#include "Engine.h"
#include "EngineSystem.h"
#include "Component.h"
#include <iostream>
#include "Pool.h"
#include "GameObjectFactory.h"

class TestComponent : public Component 
{
public:
	TestComponent(Handle<GameObject> parentObject);

	template<typename... ResetArgs>
	static Handle<Component> AddComponent(Handle<GameObject> parentObject,ResetArgs... arguments);

	template<typename... ResetArgs>
	static void RemoveComponent(ComponentHandle cHandle, ResetArgs... arguments);

	static Handle<EngineSystem> GetSystemHandle();
private:
	static Handle<EngineSystem> sysHandle;
public:
	void Reset(Handle<GameObject> parentObject)
	{
		ParentObject = parentObject;
	}
};

template<typename... ResetArgs>
inline Handle<Component> TestComponent::AddComponent(Handle<GameObject> parentObject,ResetArgs... arguments)
{
	return static_cast<TestSystem*>(&Engine::MainInstance().SystemsManager[GetSystemHandle().GetIndex()])->GetTestComponent(parentObject, arguments...);
}

template<typename ...ResetArgs>
inline void TestComponent::RemoveComponent(ComponentHandle cHandle, ResetArgs ...arguments)
{	
	static_cast<TestSystem*>(&Engine::MainInstance().SystemsManager[GetSystemHandle().GetIndex()])->RemoveTestComponent(cHandle, arguments...);
}




class TestSystem : public EngineSystem
{
public:
	Pool<TestComponent, DEFAULT_GAMEOBJECT_COUNT> components;

	static Handle<EngineSystem> GetHandle();

	TestSystem()
	{
	}

	void Update(float deltaTime) 
	{
	}

	template<typename... Args>
	void RemoveTestComponent(ComponentHandle cHandle, Args... args) 
	{
		components.RemoveItem(Handle<TestComponent>(cHandle.GetCompHandle().GetIndex()), args...);
	}

	Handle<Component> GetTestComponent(Handle<GameObject> parentObject)
	{
		return Handle<Component>(components.GetNewItem(parentObject).GetIndex());
	}
};

#endif