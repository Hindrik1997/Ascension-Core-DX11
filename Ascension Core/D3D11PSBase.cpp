#include "D3D11PSBase.h"
#include "D3D11RenderSystem.h"
#include "Engine.h"
#include <DDSTextureLoader.h>

D3D11PixelShaderBase::D3D11PixelShaderBase(wstring fileName) : FileName(fileName)
{
	D3DReadFileToBlob(FileName.c_str(), &PS_Buffer);
	if (PS_Buffer == nullptr)
		throw "Invalid pixel shader filename!";

	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	ParentRenderer.Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);
}


D3D11PixelShaderBase::~D3D11PixelShaderBase()
{
	ReleaseCOM(PS);
	ReleaseCOM(PS_Buffer);
}

void D3D11PixelShaderBase::Set()
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	ParentRenderer.DeviceContext->PSSetShader(PS, 0, 0);
}
