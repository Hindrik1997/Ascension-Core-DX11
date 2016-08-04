//
// Created by Hindrik Stegenga on 7/23/2016.
//

#include "GameObject.h"

GameObject::GameObject(GameObjectFactory* factory, Handle<GameObject> position) : ParentFactory(factory), PositionInFactory(position)
{
	ObjectTransform = Transform();
}