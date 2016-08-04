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
	template<typename ...Args>
	inline Handle<Component> GetD3D11ModelRenderer(Handle<GameObject> parentObject, Args... args);

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

#ifdef _DEBUG
	ID3D11Debug* debug = nullptr;
#endif

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
	
	//Clear depthstencil
	Renderer->DeviceContext->ClearDepthStencilView(Renderer->DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//Clear background to black
	float bgColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	Renderer->DeviceContext->ClearRenderTargetView(Renderer->RenderTargetView, bgColor);


	for (size_t i = 0; i < ModelRendererPool.size(); ++i)
	{
		if(ModelRendererPool.GetStorageRef()[i].IsUsed)
		ModelRendererPool[i].Render();
	}
	Renderer->SwapChain->Present(0, 0);
}

inline XMMATRIX D3D11RenderSystem::GetProjectionMatrix() const
{
	return XMLoadFloat4x4(&ProjectionMatrix);
}
inline XMMATRIX D3D11RenderSystem::GetViewMatrix() const
{
	return XMLoadFloat4x4(&ViewMatrix);
};

template<typename ...Args>
inline Handle<Component> D3D11RenderSystem::GetD3D11ModelRenderer(Handle<GameObject> parentObject, Args ...args)
{
	std::lock_guard<std::mutex> guard(MRPMutex);
	return Handle<Component>(ModelRendererPool.GetNewItem(parentObject, args...).GetIndex());
}

template<typename ...Args>
inline void D3D11RenderSystem::RemoveD3D11ModelRenderer(ComponentHandle cHandle, Args ...args)
{
	std::lock_guard<std::mutex> guard(MRPMutex);
	ModelRendererPool.RemoveItem(Handle<D3D11ModelRenderer>(cHandle.GetCompHandle().GetIndex()), args...);
}

#endif