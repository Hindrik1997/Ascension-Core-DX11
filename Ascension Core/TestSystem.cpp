//
// Created by Hindrik Stegenga on 7/31/2016.
//

#include "TestSystem.h"
#include "Engine.h"
#include "SystemManager.h"

Handle<EngineSystem> TestComponent::sysHandle;

TestComponent::TestComponent(Handle<GameObject> parentObject) : Component(parentObject)
{

}

Handle<EngineSystem> TestComponent::GetSystemHandle()
{
	return (sysHandle.GetIndex() == -1) ? TestSystem::GetHandle() : sysHandle;
}

Handle<EngineSystem> TestSystem::GetHandle()
{
	for (size_t i = 0; i < Engine::MainInstance().SystemsManager.GetSystems().size(); ++i)
	{
		if (typeid(TestSystem) == typeid(*(Engine::MainInstance().SystemsManager.GetSystems())[i]))
		{
			return Handle<EngineSystem>(static_cast<int>(i));
		}
	}
	throw "System not found in engine!";
}
