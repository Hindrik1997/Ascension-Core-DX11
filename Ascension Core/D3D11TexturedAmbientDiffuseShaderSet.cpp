#include "D3D11TexturedAmbientDiffuseShaderSet.h"
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#include "D3D11RenderSystem.h"
#include "Engine.h"
#include "CoreSystem.h"

#define START_SLOT 0
#define NUM_BUFFERS 1

D3D11TexturedAmbientDiffuseShaderSet::D3D11TexturedAmbientDiffuseShaderSet(wstring fileName) : ps(L"TexturedAmbientDiffusePS.cso"), vs(L"TexturedAmbientDiffuseVS.cso")
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

	ConstantBufferStructurePerObject = new PerObjectBufferStructTAD;
	ConstantBufferStructurePerFrame = new PerFrameBufferStructTAD;

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(PerObjectBufferStructTAD);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = NULL;
	bufferDesc.MiscFlags = NULL;
	ParentRenderer.Device->CreateBuffer(&bufferDesc, NULL, &PerObjectBuffer);

	D3D11_BUFFER_DESC bufferDesc2;
	ZeroMemory(&bufferDesc2, sizeof(D3D11_BUFFER_DESC));

	bufferDesc2.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc2.ByteWidth = sizeof(PerObjectBufferStructTAD);
	bufferDesc2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc2.CPUAccessFlags = NULL;
	bufferDesc2.MiscFlags = NULL;
	ParentRenderer.Device->CreateBuffer(&bufferDesc2, NULL, &PerFrameBuffer);
}


D3D11TexturedAmbientDiffuseShaderSet::~D3D11TexturedAmbientDiffuseShaderSet()
{
	ReleaseCOM(TextureSampler);
	ReleaseCOM(Texture);

	ReleaseCOM(PerObjectBuffer);
	ReleaseCOM(PerFrameBuffer);

	if (ConstantBufferStructurePerObject != nullptr)
		delete ConstantBufferStructurePerObject;

	if (ConstantBufferStructurePerFrame != nullptr)
		delete ConstantBufferStructurePerFrame;
}

void D3D11TexturedAmbientDiffuseShaderSet::Set(D3D11ModelRenderer& renderer)
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	
	ParentRenderer.DeviceContext->RSGetState(&RSPrevState);
	ParentRenderer.DeviceContext->RSSetState(NULL);

	vs.Set();
	ps.Set();
	
	ParentRenderer.DeviceContext->VSSetConstantBuffers(START_SLOT, NUM_BUFFERS, &PerObjectBuffer);
	ParentRenderer.DeviceContext->PSSetConstantBuffers(START_SLOT, NUM_BUFFERS, &PerFrameBuffer);
	ParentRenderer.DeviceContext->PSSetShaderResources(0, 1, &Texture);
	ParentRenderer.DeviceContext->PSSetSamplers(0, 1, &TextureSampler);

	

	//Update per frame buffer
	XMFLOAT4 Ambient;
	Vector3f a = Engine::MainInstance().SystemsManager.GetCoreSystem().GetAmbientColor();
	Ambient.x = a.x / 255.0f; Ambient.y = a.y / 255.0f; Ambient.z = a.z / 255.0f;
	Ambient.w = Engine::MainInstance().SystemsManager.GetCoreSystem().GetAmbientIntensity();
	//Mappen naar 0.0f - 1.0f range
	Ambient.w = Ambient.w / 255.0f;
		
	ConstantBufferStructurePerFrame->AmbientColor = Ambient;
	ParentRenderer.DeviceContext->UpdateSubresource(PerFrameBuffer, 0, NULL, &*ConstantBufferStructurePerFrame, 0, 0);
}

void D3D11TexturedAmbientDiffuseShaderSet::Update(D3D11ModelRenderer& renderer)
{

	XMMATRIX WVP = renderer.GetWorldViewProjectionMatrix();

	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;

	ConstantBufferStructurePerObject->WVP = XMMatrixTranspose(WVP);
	ParentRenderer.DeviceContext->UpdateSubresource(PerObjectBuffer, 0, NULL, &*ConstantBufferStructurePerObject, 0, 0);
}

void D3D11TexturedAmbientDiffuseShaderSet::RevertState(D3D11ModelRenderer & renderer)
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	ParentRenderer.DeviceContext->RSSetState(RSPrevState);
	RSPrevState = nullptr;
}
