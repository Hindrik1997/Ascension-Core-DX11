//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_ENGINESYSTEM_H
#define ASCENSION_CORE_ENGINESYSTEM_H

#include <typeinfo>
#include "Handle.h"

class Component;
class Engine;

class EngineSystem {
public:
    EngineSystem();
    virtual ~EngineSystem() = 0;

	//Updates every frame is done here
	virtual void Update(float deltaTime) = 0;
};

#endif //ASCENSION_CORE_ENGINESYSTEM_H
