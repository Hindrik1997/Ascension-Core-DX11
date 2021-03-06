//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_GAMEOBJECTFACTORY_H
#define ASCENSION_CORE_GAMEOBJECTFACTORY_H

#include "Handle.h"
#include "Pool.h"
#include "GameObject.h"
#include <mutex>
#include "Limits.h"

using std::mutex;

class Engine;

class GameObjectFactory {
private:
	friend class Engine;
    GameObjectFactory();
public:
	//Does not include bounds checking!
	GameObject& operator[] (const int index);

	//Does not include bounds checking!
	GameObject& operator[] (const Handle<GameObject> handle);

	//Does include bounds checking
	GameObject& at(const int index);

	//Does include bounds checking
	GameObject& at(const Handle<GameObject> handle);


    inline Handle<GameObject> CreateGameObject();
    inline void DeleteGameObject(Handle<GameObject> objectHandle);

private:
	mutex GMutex;
    Pool<GameObject, DEFAULT_GAMEOBJECT_COUNT> GameObjects;
};

inline GameObject& GameObjectFactory::at(const int index)
{
	if (index >= 0 && index <= static_cast<int>(GameObjects.size()) - 1)
		return GameObjects[index];
	throw "Out of bounds!";
}

inline GameObject & GameObjectFactory::at(const Handle<GameObject> handle)
{
	if (handle.GetIndex() >= 0 && handle.GetIndex() <= static_cast<int>(GameObjects.size()) - 1)
		return GameObjects[handle.GetIndex()];
	throw "Out of bounds!";
}

inline Handle<GameObject> GameObjectFactory::CreateGameObject()
{
	std::lock_guard<std::mutex> guard(GMutex);
	Handle<GameObject> position(GameObjects.GetFirstFreeIndex());
    return GameObjects.GetNewItem(position);
}

inline void GameObjectFactory::DeleteGameObject(Handle<GameObject> objectHandle)
{
	std::lock_guard<std::mutex> guard(GMutex);
    GameObjects.RemoveItem(objectHandle);
}

#endif //ASCENSION_CORE_GAMEOBJECTFACTORY_H