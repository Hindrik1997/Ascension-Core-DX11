//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_D3D11RENDERSYSTEM_H
#define ASCENSION_CORE_D3D11RENDERSYSTEM_H
#include <DirectXMath.h>
#include <memory>
#include "RenderSystem.h"
#include "Win32Window.h"
#include "D3D11Renderer.h"
#include "D3D11ModelRenderer.h"
#include "GameObjectFactory.h"

using namespace DirectX;
using std::unique_ptr;

class D3D11RenderSystem : public RenderSystem
{
public:
	D3D11RenderSystem(int width, int height);
	~D3D11RenderSystem();
public:
	inline bool ProcessAPI();
	inline void Render();
	inline XMMATRIX GetProjectionMatrix() const;
	inline XMMATRIX GetViewMatrix() const;
	XMMATRIX RecalculateProjectionMatrix();
	XMMATRIX RecalculateViewMatrix();
	virtual void Update(float deltaTime);

	//Component stuff

	inline Handle<Component> GetD3D11ModelRenderer(Handle<GameObject> parentObject);

	template<typename... Args>
	inline void RemoveD3D11ModelRenderer(ComponentHandle cHandle, Args... args);

	static Handle<EngineSystem> GetHandle();

	//Models, textures, meshes and shaders

	void LoadVertexShader(wstring name);
	void LoadPixelShader(wstring name);
	void LoadMesh(wstring name);

	void UnLoadVertexShader(wstring name);
	void UnLoadPixelShader(wstring name);
	void UnLoadMesh(wstring name);

public:
	unique_ptr<Win32Window<D3D11Renderer>> MainWindow;
	unique_ptr<D3D11Renderer> Renderer;

private:
	XMFLOAT4X4 ProjectionMatrix;
	XMFLOAT4X4 ViewMatrix;

	mutex MRPMutex;
	Pool<D3D11ModelRenderer, DEFAULT_SIZE> ModelRendererPool;

private:
	//Resources




};

inline bool D3D11RenderSystem::ProcessAPI()
{
	return MainWindow->ProcessMessages();
};

inline void D3D11RenderSystem::Render()
{
	return Renderer->Render();
}

inline XMMATRIX D3D11RenderSystem::GetProjectionMatrix() const
{
	return XMLoadFloat4x4(&ProjectionMatrix);
}
inline XMMATRIX D3D11RenderSystem::GetViewMatrix() const
{
	return XMLoadFloat4x4(&ViewMatrix);
};

inline Handle<Component> D3D11RenderSystem::GetD3D11ModelRenderer(Handle<GameObject> parentObject)
{
	std::lock_guard<std::mutex> guard(MRPMutex);
	return Handle<Component>(ModelRendererPool.GetNewItem(parentObject).GetIndex());
}

template<typename ...Args>
inline void D3D11RenderSystem::RemoveD3D11ModelRenderer(ComponentHandle cHandle, Args ...args)
{
	std::lock_guard<std::mutex> guard(MRPMutex);
	ModelRendererPool.RemoveItem(Handle<D3D11ModelRenderer>(cHandle.CompHandle.GetIndex()), args...);
}

#endif