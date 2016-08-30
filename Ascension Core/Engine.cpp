//
// Created by Hindrik Stegenga on 7/23/2016.
//

#include "Engine.h"
#include <iostream>
#include "TestSystem.h"
#include "D3D11RenderSystem.h"
#include <functional>

Engine* Engine::MainInstancePointer = nullptr;
char Engine::ConstructCounter = 0;

Engine::Engine()
{
	if (ConstructCounter == 0)
	{
		ConstructCounter++;
		SetMainInstance(this);
	}
	else
		throw "Only one instance allowed!";
}

Engine::~Engine()
{
}

Engine& Engine::MainInstance()
{
	return *MainInstancePointer;
}

void Engine::GameLoop()
{	
	std::cout << "started game loop" << std::endl;
	while (true)
	{
		//Process window messages
		bool MessageResult = SystemsManager.GetRenderSystem().ProcessAPI();
		if (!MessageResult)
			break;

		//Calculate frame time and deltatime
		double frameTime = GameTimer.FrameTimeCalculations();

		D3D11RenderSystem& RSystem = *static_cast<D3D11RenderSystem*>(&SystemsManager.GetRenderSystem());
		wstring text;
		text += L"ASCENSION GAME ENGINE - ";
		text += std::to_wstring(frameTime);
		text += L" - ";
		text += std::to_wstring(GameTimer.Fps);
		text += L" FPS";
		SetWindowText(RSystem.MainWindow->hWnd, text.c_str());


		//Update systems using frame time
		SystemsManager.UpdateSystems(static_cast<float>(frameTime));

		//Render everything
		SystemsManager.GetRenderSystem().Render();
	}	
}

void Engine::SetMainInstance(Engine* engine)
{
	MainInstancePointer = engine;
}
