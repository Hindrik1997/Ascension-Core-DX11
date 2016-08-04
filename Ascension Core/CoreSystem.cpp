#include "CoreSystem.h"
#include "Engine.h"

CoreSystem::CoreSystem()
{
	
}

void CoreSystem::Update(float deltaTime)
{
}

Handle<Component> CoreSystem::GetCamera(Handle<GameObject> parentObject)
{
	return Handle<Component>(cameras.GetNewItem(parentObject).GetIndex());
}

CoreSystem::~CoreSystem()
{
}

Handle<EngineSystem> CoreSystem::GetHandle()
{
	for (size_t i = 0; i < Engine::MainInstance().SystemsManager.GetSystems().size(); ++i)
	{
		if (typeid(CoreSystem) == typeid(*(Engine::MainInstance().SystemsManager.GetSystems())[i]))
		{
			return Handle<EngineSystem>(i);
		}
	}
	throw "System not found in engine!";
}