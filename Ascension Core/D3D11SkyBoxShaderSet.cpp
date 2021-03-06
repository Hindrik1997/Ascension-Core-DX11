#include "D3D11SkyBoxShaderSet.h"
#include <DDSTextureLoader.h>
#include "D3D11RenderSystem.h"
#include "Engine.h"
#include "CoreSystem.h"
#include "Camera.h"

#define START_SLOT 0
#define NUM_BUFFERS 1

D3D11SkyBoxShaderSet::D3D11SkyBoxShaderSet(wstring fileName) : ps(L"SkyBoxPS.cso"), vs(L"SkyBoxVS.cso")
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;

	CheckFail(CreateDDSTextureFromFile(ParentRenderer.Device, fileName.c_str(), NULL, &SkyBoxTexture), L"Error getting cubemap");

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	sampDesc.MipLODBias = 0.0f;
	sampDesc.MaxAnisotropy = 16;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = 0;

	CheckFail(ParentRenderer.Device->CreateSamplerState(&sampDesc, &SkyBoxSampler), L"Error creating sampler state");

	D3D11_RASTERIZER_DESC wfdesc;
	ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
	wfdesc.CullMode = D3D11_CULL_FRONT;
	wfdesc.FillMode = D3D11_FILL_SOLID;
	ParentRenderer.Device->CreateRasterizerState(&wfdesc, &NoCullState);

	ConstantBufferStructure = new PerObjectBufferStruct;

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(PerObjectBufferStruct);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = NULL;
	bufferDesc.MiscFlags = NULL;
	ParentRenderer.Device->CreateBuffer(&bufferDesc, NULL, &PerObjectBuffer);

	D3D11_DEPTH_STENCIL_DESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dsdesc.DepthEnable = true;
	dsdesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsdesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	ParentRenderer.Device->CreateDepthStencilState(&dsdesc, &DSLessEqualState);
}


D3D11SkyBoxShaderSet::~D3D11SkyBoxShaderSet()
{
	ReleaseCOM(SkyBoxSampler);
	ReleaseCOM(SkyBoxTexture);
	ReleaseCOM(NoCullState);

	if (ConstantBufferStructure != nullptr)
		delete ConstantBufferStructure;
}

void D3D11SkyBoxShaderSet::Set(D3D11ModelRenderer& renderer)
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	
	ParentRenderer.DeviceContext->OMGetDepthStencilState(&DsSPrevState,0);
	ParentRenderer.DeviceContext->RSGetState(&RSPrevState);

	ParentRenderer.DeviceContext->OMSetDepthStencilState(DSLessEqualState, 0);
	ParentRenderer.DeviceContext->RSSetState(NoCullState);


	vs.Set();
	ps.Set();
	ParentRenderer.DeviceContext->VSSetConstantBuffers(START_SLOT, NUM_BUFFERS, &PerObjectBuffer);
	
	ParentRenderer.DeviceContext->PSSetShaderResources(0, 1, &SkyBoxTexture);
	ParentRenderer.DeviceContext->PSSetSamplers(0, 1, &SkyBoxSampler);
}

void D3D11SkyBoxShaderSet::Update(D3D11ModelRenderer& renderer)
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11RenderSystem& RS = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle]);
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;

	Camera& CurrentCamera = Engine::MainInstance().SystemsManager.GetRenderSystem().GetCamera();
	GameObject& Parent = Engine::MainInstance().ObjectsFactory[CurrentCamera.ParentObject];

	XMMATRIX World = XMMatrixIdentity();
	World = XMMatrixTranslationFromVector(XMVectorSet(Parent.ObjectTransform.Position.x, Parent.ObjectTransform.Position.y, Parent.ObjectTransform.Position.z, 1.0f));

	XMMATRIX WVP = World * RS.RecalculateViewMatrix() * RS.RecalculateProjectionMatrix();

	ConstantBufferStructure->WVP = XMMatrixTranspose(WVP);
	ParentRenderer.DeviceContext->UpdateSubresource(PerObjectBuffer, 0, NULL, &*ConstantBufferStructure, 0, 0);
}

void D3D11SkyBoxShaderSet::RevertState(D3D11ModelRenderer& renderer)
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	ParentRenderer.DeviceContext->OMSetDepthStencilState(DsSPrevState, 0);
	ParentRenderer.DeviceContext->RSSetState(RSPrevState);
	DsSPrevState = nullptr;
	RSPrevState = nullptr;
}
