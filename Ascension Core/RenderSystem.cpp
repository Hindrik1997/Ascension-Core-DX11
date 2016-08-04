//
// Created by Hindrik Stegenga on 7/23/2016.
//

#include "RenderSystem.h"
#include "HelperFunctions.h"
#include "CoreSystem.h"

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem() {

}

void RenderSystem::SetCamera(ComponentHandle cHandle)
{
}

Camera& RenderSystem::GetCamera()
{
	return static_cast<CoreSystem*>(&Engine::MainInstance().SystemsManager[CurrentMainCamera.GetSysHandle()])->cameras[CurrentMainCamera.GetCompHandle().GetIndex()];
}
