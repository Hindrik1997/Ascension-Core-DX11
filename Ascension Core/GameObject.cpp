//
// Created by Hindrik Stegenga on 7/23/2016.
//

#include "GameObject.h"

GameObject::GameObject(Handle<GameObject> position) : PositionInFactory(position)
{
	ObjectTransform = Transform();
}