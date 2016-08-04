//
// Created by Hindrik Stegenga on 7/25/2016.
//

#include "Component.h"
#include "Engine.h"

Component::Component(Handle<GameObject> parentObject) : ParentObject(parentObject)
{
}

Handle<Component> Component::AddComponent()
{
	throw "Default component not allowed! Is your component correctly implemented?"; 
}

void Component::RemoveComponent()
{
	throw "Default component not allowed! Is your component correctly implemented?";
}