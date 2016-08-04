//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_ENGINE_H
#define ASCENSION_CORE_ENGINE_H

#include "SystemManager.h"
#include "Timer.h"
#include "GameObjectFactory.h"

class Engine {
public:
    Engine();
    ~Engine();

	GameObjectFactory ObjectsFactory;
    SystemManager SystemsManager;
	static Engine& MainInstance();
private:
	static char ConstructCounter;
	static Engine* MainInstancePointer;
	Timer GameTimer;
public:
    void GameLoop();
private:
	void SetMainInstance(Engine* engine);
};


#endif //ASCENSION_CORE_ENGINE_H
