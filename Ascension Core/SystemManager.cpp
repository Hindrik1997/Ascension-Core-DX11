//
// Created by Hindrik Stegenga on 7/23/2016.
//

#include "SystemManager.h"
#include "CoreSystem.h"

SystemManager::~SystemManager()
{

}

SystemManager::SystemManager()
{
	CurrentCoreSystem = AddSystem<CoreSystem>();
}

EngineSystem& SystemManager::operator[](const int index)
{
	return *Systems[index];
}

EngineSystem& SystemManager::operator[](const Handle<EngineSystem> handle)
{
	return *Systems[handle.GetIndex()];
}

EngineSystem& SystemManager::at(const int index)
{
	if (index > 0 && index < static_cast<int>(Systems.size()))
		return *Systems[index];
	throw "Out of bounds error!";
}

EngineSystem& SystemManager::at(const Handle<EngineSystem> handle)
{
	if (handle.GetIndex() > 0 && handle.GetIndex() < static_cast<int>(Systems.size()))
		return *Systems[handle.GetIndex()];
	throw "Out of bounds error!";
}

void SystemManager::UpdateSystems(float deltaTime) const
{
	for (size_t i = 0; i < Systems.size(); ++i)
	{
		Systems[i]->Update(deltaTime);
	}
}

void SystemManager::RemoveSystem(const int index)
{
	std::lock_guard<std::mutex> guard(CSMutex);
	Systems.erase(Systems.begin() + index);
}

void SystemManager::RemoveSystem(const Handle<EngineSystem> handle)
{
	std::lock_guard<std::mutex> guard(CSMutex);
	Systems.erase(Systems.begin() + handle.GetIndex());
}

CoreSystem& SystemManager::GetCoreSystem() 
{
	return *static_cast<CoreSystem*>(Systems[CurrentCoreSystem.GetIndex()].get());
}
