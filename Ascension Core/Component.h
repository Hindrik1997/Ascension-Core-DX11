//
// Created by Hindrik Stegenga on 7/25/2016.
//

#ifndef ASCENSION_CORE_COMPONENT_H
#define ASCENSION_CORE_COMPONENT_H

#include "Handle.h"
#include <typeinfo>

class Engine;
class GameObject;

class Component {
public:
	Handle<GameObject> ParentObject;
	Component(Handle<GameObject> parentObject);

	static Handle<Component> AddComponent();
	static void RemoveComponent();
};


#endif //ASCENSION_CORE_COMPONENT_H
