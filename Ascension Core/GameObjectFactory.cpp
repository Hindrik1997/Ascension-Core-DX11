//
// Created by Hindrik Stegenga on 7/23/2016.
//

#include "GameObjectFactory.h"

GameObjectFactory::GameObjectFactory()
{

}

GameObject& GameObjectFactory::operator[](const int index)
{
	return GameObjects[index];
}
