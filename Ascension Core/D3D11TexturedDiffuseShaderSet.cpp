#include "D3D11TexturedDiffuseShaderSet.h"
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#include "D3D11RenderSystem.h"
#include "Engine.h"

#define START_SLOT 0
#define NUM_BUFFERS 1

D3D11TexturedDiffuseShaderSet::D3D11TexturedDiffuseShaderSet(wstring fileName) : ps(L"TexturedDiffusePS.cso"), vs(L"TexturedDiffuseVS.cso")
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	
	HRESULT hr = CreateDDSTextureFromFile(ParentRenderer.Device, fileName.c_str(), NULL, &Texture);
	if (!SUCCEEDED(hr))
	{
		hr = CreateWICTextureFromFile(ParentRenderer.Device, fileName.c_str(), NULL, &Texture);
		if (!SUCCEEDED(hr))
			throw "Could not load the specified texture";
	}


	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.MipLODBias = 0.0f;
	sampDesc.MaxAnisotropy = 16;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_EQUAL;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = 4;

	CheckFail(ParentRenderer.Device->CreateSamplerState(&sampDesc, &TextureSampler), L"Error creating sampler state");

	ConstantBufferStructure = new PerObjectBufferStructTD;

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(PerObjectBufferStructTD);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = NULL;
	bufferDesc.MiscFlags = NULL;
	ParentRenderer.Device->CreateBuffer(&bufferDesc, NULL, &PerObjectBuffer);
}


D3D11TexturedDiffuseShaderSet::~D3D11TexturedDiffuseShaderSet()
{
	ReleaseCOM(TextureSampler);
	ReleaseCOM(Texture);

	if (ConstantBufferStructure != nullptr)
		delete ConstantBufferStructure;
}

void D3D11TexturedDiffuseShaderSet::Set(D3D11ModelRenderer& renderer)
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	
	ParentRenderer.DeviceContext->RSGetState(&RSPrevState);
	ParentRenderer.DeviceContext->RSSetState(NULL);

	vs.Set();
	ps.Set();

	ParentRenderer.DeviceContext->VSSetConstantBuffers(START_SLOT, NUM_BUFFERS, &PerObjectBuffer);

	ParentRenderer.DeviceContext->PSSetShaderResources(0, 1, &Texture);
	ParentRenderer.DeviceContext->PSSetSamplers(0, 1, &TextureSampler);
}

void D3D11TexturedDiffuseShaderSet::Update(D3D11ModelRenderer& renderer)
{

	XMMATRIX WVP = renderer.GetWorldViewProjectionMatrix();

	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;

	ConstantBufferStructure->WVP = XMMatrixTranspose(WVP);
	ParentRenderer.DeviceContext->UpdateSubresource(PerObjectBuffer, 0, NULL, &*ConstantBufferStructure, 0, 0);
}

void D3D11TexturedDiffuseShaderSet::RevertState(D3D11ModelRenderer& renderer)
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	ParentRenderer.DeviceContext->RSSetState(RSPrevState);
	RSPrevState = nullptr;
}
