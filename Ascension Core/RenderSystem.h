//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_RENDERSYSTEM_H
#define ASCENSION_CORE_RENDERSYSTEM_H

#include "Component.h"
#include "EngineSystem.h"
#include <string>
#include "ComponentHandle.h"
#include "Camera.h"

using std::wstring;

class RenderSystem : public EngineSystem
{
public:
    RenderSystem();
    ~RenderSystem();

public:
    virtual bool ProcessAPI() = 0;
    virtual void Render() = 0;
	virtual void Update(float deltaTime) = 0;

	//Loadmesh, texture,shader etc.

	virtual void LoadVertexShader(wstring name) = 0;
	virtual void LoadPixelShader(wstring name) = 0;
	virtual void LoadMesh(wstring name) = 0;

	virtual void UnLoadVertexShader(wstring name) = 0;
	virtual void UnLoadPixelShader(wstring name) = 0;
	virtual void UnLoadMesh(wstring name) = 0;

	void SetCamera(ComponentHandle cHandle);
	Camera& GetCamera();

private:
	ComponentHandle CurrentMainCamera;
};

#endif //ASCENSION_CORE_RENDERSYSTEM_H
