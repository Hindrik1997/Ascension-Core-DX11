//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_SYSTEMMANAGER_H
#define ASCENSION_CORE_SYSTEMMANAGER_H

#include "Handle.h"
#include "EngineSystem.h"
#include "RenderSystem.h"
#include "Pool.h"
#include <vector>
#include <memory>
#include <mutex>

using std::unique_ptr;
using std::vector;
using std::mutex;

class SystemManager {
public:
    SystemManager();
    ~SystemManager();
public:
	//Adds system
    template<typename T, typename... CustomArgs> 
	Handle<EngineSystem> AddSystem(CustomArgs... arguments);

	template<typename T, typename... CustomArgs>
	Handle<EngineSystem> AddRenderSystem(CustomArgs... arguments);

	//Invalidates all handles to your custom systems and will probably crash everything!
	void RemoveSystem(const int index);
	
	//Invalidates all handles to your custom systems and wil probably crash everything!
	void RemoveSystem(const Handle<EngineSystem> handle);
public:
	//Does not include bound checking!
	EngineSystem& operator[] (const int index);
	
	//Does not include bound checking!
	EngineSystem& operator[] (const Handle<EngineSystem> handle);
	
	//Includes bound checking
	EngineSystem& at(const int index);
	
	//Includes bound checking
	EngineSystem& at(const Handle<EngineSystem> handle);
public:
	//Updates all systems, requires frametime. Will be invoked in GameLoop()
	void UpdateSystems(float deltaTime) const;

	//Provides a const vector reference to the systems
	inline const vector<unique_ptr<EngineSystem>>& GetSystems() const;
    
	//Gets reference to current render system.
	RenderSystem& GetRenderSystem();
private:
	Handle<EngineSystem> CurrentRenderSystem;

	mutex CSMutex;
	vector<unique_ptr<EngineSystem>> Systems;
};

template<typename T, typename ...CustomArgs>
inline Handle<EngineSystem> SystemManager::AddSystem(CustomArgs ...arguments)
{
	std::lock_guard<std::mutex> guard(CSMutex);
	Systems.push_back(std::make_unique<T>(arguments...));
	return Handle<EngineSystem>(Systems.size() - 1);
}

template<typename T, typename ...CustomArgs>
inline Handle<EngineSystem> SystemManager::AddRenderSystem(CustomArgs ...arguments)
{
	Handle<EngineSystem> h = AddSystem<T>(arguments...);
	CurrentRenderSystem = h;
	return h;
}

inline const vector<unique_ptr<EngineSystem>>& SystemManager::GetSystems() const
{
	return Systems;
}

inline RenderSystem& SystemManager::GetRenderSystem()
{
	return *static_cast<RenderSystem*>(Systems[CurrentRenderSystem.GetIndex()].get());
}

#endif //ASCENSION_CORE_SYSTEMMANAGER_H