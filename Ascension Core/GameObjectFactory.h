//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_GAMEOBJECTFACTORY_H
#define ASCENSION_CORE_GAMEOBJECTFACTORY_H

#include "Handle.h"
#include "Pool.h"
#include "GameObject.h"
#include <mutex>

#define DEFAULT_SIZE 65535

using std::mutex;

class Engine;

class GameObjectFactory {
public:
    GameObjectFactory();

	//Does not include bounds checking!
	GameObject& operator[] (const int index);

	//Does include bounds checking
	GameObject& at(const int index);

    inline Handle<GameObject> CreateGameObject();
    inline void DeleteGameObject(Handle<GameObject> objectHandle);

private:
	mutex GMutex;
    Pool<GameObject, DEFAULT_SIZE> GameObjects;
};

inline GameObject& GameObjectFactory::at(const int index)
{
	if (index >= 0 && index <= static_cast<int>(GameObjects.size()) - 1)
		return GameObjects[index];
	throw "Out of bounds!";
}

inline Handle<GameObject> GameObjectFactory::CreateGameObject()
{
	std::lock_guard<std::mutex> guard(GMutex);
	Handle<GameObject> position(GameObjects.GetFirstFreeIndex());
    return GameObjects.GetNewItem(this, position);
}

inline void GameObjectFactory::DeleteGameObject(Handle<GameObject> objectHandle)
{
	std::lock_guard<std::mutex> guard(GMutex);
    GameObjects.RemoveItem(objectHandle);
}

#endif //ASCENSION_CORE_GAMEOBJECTFACTORY_H