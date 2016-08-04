//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_GAMEOBJECT_H
#define ASCENSION_CORE_GAMEOBJECT_H

#include "Transform.h"
#include "ComponentHandle.h"
#include "Component.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

template<typename T>
class PoolItem;

class GameObjectFactory;
class ComponentHandle;

class GameObject {
private:
	friend class PoolItem<GameObject>;
    GameObject(Handle<GameObject> position);
public:
    //only movable
    GameObject(GameObject&& source) = delete;
    GameObject& operator=(GameObject&& source) = delete;
    //non-copyable
    GameObject(const GameObject& source) = delete;
    GameObject& operator=(const GameObject& source) = delete;
public:
	Transform ObjectTransform;
	Handle<GameObject> PositionInFactory;
	string Name = "GameObject";
    
	template<typename T, typename... ResetArgs> inline ComponentHandle AddComponent(ResetArgs... arguments);
	template<typename T, typename... ResetArgs> inline void RemoveComponent(ComponentHandle cHandle, ResetArgs... arguments);

private:
    vector<ComponentHandle> components;
};

template<typename T, typename... ResetArgs>
inline ComponentHandle GameObject::AddComponent(ResetArgs... arguments)
{
	ComponentHandle cHandle(T::AddComponent(PositionInFactory, arguments...) ,T::GetSystemHandle());
	components.push_back(cHandle);
	return cHandle;
}

template<typename T, typename... ResetArgs>
inline void GameObject::RemoveComponent(ComponentHandle cHandle, ResetArgs... arguments)
{
	T::RemoveComponent(cHandle, arguments...);
}




#endif //ASCENSION_CORE_GAMEOBJECT_H