//
// Created by Hindrik Stegenga on 8/1/2016.
//

#include "D3D11VSBase.h"
#include <chrono>
#include "D3D11RenderSystem.h"
#include "Engine.h"


#define START_SLOT 0
#define NUM_BUFFERS 1

D3D11VertexShaderBase::D3D11VertexShaderBase(wstring fileName) : FileName(fileName)
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;

	D3DReadFileToBlob(FileName.c_str(), &VS_Buffer);

	if (VS_Buffer == nullptr)
		throw "Invalid pixel shader filename!";

	ParentRenderer.Device->CreateInputLayout(D3D11Vertex::Layout, D3D11Vertex::LayoutSize, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &InputLayout);
	ParentRenderer.Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
}

void D3D11VertexShaderBase::SetInputLayout()
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	ParentRenderer.DeviceContext->IASetInputLayout(InputLayout);
}

D3D11VertexShaderBase::~D3D11VertexShaderBase()
{
	ReleaseCOM(VS);
	ReleaseCOM(VS_Buffer);
	ReleaseCOM(InputLayout);
}

void D3D11VertexShaderBase::Set()
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& renderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	SetInputLayout();
	renderer.DeviceContext->VSSetShader(VS, 0, 0);
}