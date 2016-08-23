#include "D3D11StandardShaderSet.h"
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#include "D3D11RenderSystem.h"
#include "Engine.h"
#include "CoreSystem.h"
#include "Pool.h"

#define START_SLOT 0
#define NUM_BUFFERS 1

D3D11StandardShaderSet::D3D11StandardShaderSet(wstring fileName) : ps(L"StandardPS.cso"), vs(L"StandardVS.cso")
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

	VSConstanBufferStructurePerFrame = new VSPerFrameBufferStructSTD;

	VSConstantBufferStructurePerObject = new VSPerObjectBufferStructSTD;

	PSConstantBufferStructurePerFrame = new PSPerFrameBufferStructSTD;

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(VSPerObjectBufferStructSTD);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = NULL;
	bufferDesc.MiscFlags = NULL;
	ParentRenderer.Device->CreateBuffer(&bufferDesc, NULL, &VSPerObjectBuffer);

	D3D11_BUFFER_DESC bufferDesc2;
	ZeroMemory(&bufferDesc2, sizeof(D3D11_BUFFER_DESC));

	bufferDesc2.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc2.ByteWidth = sizeof(PSPerFrameBufferStructSTD);
	bufferDesc2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc2.CPUAccessFlags = NULL;
	bufferDesc2.MiscFlags = NULL;
	ParentRenderer.Device->CreateBuffer(&bufferDesc2, NULL, &PSPerFrameBuffer);

	D3D11_BUFFER_DESC bufferDesc3;
	ZeroMemory(&bufferDesc3, sizeof(D3D11_BUFFER_DESC));

	bufferDesc3.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc3.ByteWidth = sizeof(PSPerFrameBufferStructSTD);
	bufferDesc3.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc3.CPUAccessFlags = NULL;
	bufferDesc3.MiscFlags = NULL;
	ParentRenderer.Device->CreateBuffer(&bufferDesc3, NULL, &VSPerFrameBuffer);

}


D3D11StandardShaderSet::~D3D11StandardShaderSet()
{
	ReleaseCOM(TextureSampler);
	ReleaseCOM(Texture);

	ReleaseCOM(VSPerFrameBuffer);
	ReleaseCOM(VSPerObjectBuffer);
	ReleaseCOM(PSPerFrameBuffer);

	if (VSConstanBufferStructurePerFrame != nullptr)
		delete VSConstanBufferStructurePerFrame;

	if (VSConstantBufferStructurePerObject != nullptr)
		delete VSConstantBufferStructurePerObject;

	if (PSConstantBufferStructurePerFrame != nullptr)
		delete PSConstantBufferStructurePerFrame;
}

void D3D11StandardShaderSet::Set(D3D11ModelRenderer& renderer)
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;

	ParentRenderer.DeviceContext->RSSetState(NULL);

	vs.Set();
	ps.Set();

	ParentRenderer.DeviceContext->VSSetConstantBuffers(START_SLOT, NUM_BUFFERS, &VSPerObjectBuffer);
	ParentRenderer.DeviceContext->PSSetConstantBuffers(START_SLOT, NUM_BUFFERS, &PSPerFrameBuffer);
	ParentRenderer.DeviceContext->PSSetShaderResources(0, 1, &Texture);
	ParentRenderer.DeviceContext->PSSetSamplers(0, 1, &TextureSampler);

	//AMBIENT LIGHT

	//Update per frame buffer
	XMFLOAT4 Ambient;
	Vector3f a = Engine::MainInstance().SystemsManager.GetCoreSystem().lightManager.GetAmbientColor();
	Ambient.x = a.x / 255.0f; Ambient.y = a.y / 255.0f; Ambient.z = a.z / 255.0f;
	Ambient.w = Engine::MainInstance().SystemsManager.GetCoreSystem().lightManager.GetAmbientIntensity();
	//Mappen naar 0.0f - 1.0f range
	Ambient.w = Ambient.w / 255.0f;

	PSConstantBufferStructurePerFrame->AmbientColor = Ambient;

	CoreSystem& Cs = Engine::MainInstance().SystemsManager.GetCoreSystem();
	DLPool& lightList = const_cast<DLPool&>(Cs.lightManager.GetDirectionalLightsList());

	int isValid = 0;

	for (int i = 0; i < LIGHT_COUNT_PS; ++i)
	{
		if (lightList.GetStorageRef()[i].IsUsed)
		{
			PSConstantBufferStructurePerFrame->DirectionalLights[i] = DirectionalLightShaderStruct
			{
				XMFLOAT3(lightList[i].GetDirection().x, lightList[i].GetDirection().y, lightList[i].GetDirection().z),
				XMFLOAT4(lightList[i].GetColor().x, lightList[i].GetColor().y, lightList[i].GetColor().z, lightList[i].GetIntensity())
			};
			isValid++;
		}
	}

	PSConstantBufferStructurePerFrame->LightCount = isValid;

	ParentRenderer.DeviceContext->UpdateSubresource(PSPerFrameBuffer, 0, NULL, &*PSConstantBufferStructurePerFrame, 0, 0);
}

void D3D11StandardShaderSet::Update(D3D11ModelRenderer& renderer)
{
	XMMATRIX W = renderer.GetWorldMatrix();
	XMMATRIX WV = renderer.GetWorldViewMatrix();
	XMMATRIX WVP = renderer.GetWorldViewProjectionMatrix();

	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;

	VSConstantBufferStructurePerObject->WorldMatrix = XMMatrixTranspose(W);
	VSConstantBufferStructurePerObject->WorldViewMatrix = XMMatrixTranspose(WV);
	VSConstantBufferStructurePerObject->WorldViewProjectionMatrix = XMMatrixTranspose(WVP);

	ParentRenderer.DeviceContext->UpdateSubresource(VSPerObjectBuffer, 0, NULL, &*VSConstantBufferStructurePerObject, 0, 0);
}
