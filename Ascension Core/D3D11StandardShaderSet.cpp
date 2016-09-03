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

	HRESULT hr = CreateDDSTextureFromFile(ParentRenderer.Device, fileName.c_str(), NULL, &DiffuseMap);
	if (!SUCCEEDED(hr))
	{
		hr = CreateWICTextureFromFile(ParentRenderer.Device, fileName.c_str(), NULL, &DiffuseMap);
		if (!SUCCEEDED(hr))
			throw "Could not load the specified texture";
	}

	hr = CreateDDSTextureFromFile(ParentRenderer.Device, L"gloss.dds", NULL, &EnvironmentMap);
	if (!SUCCEEDED(hr))
	{
		hr = CreateWICTextureFromFile(ParentRenderer.Device, fileName.c_str(), NULL, &EnvironmentMap);
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

	VSConstantBufferStructurePerFrame = new VSPerFrameBufferStructSTD;
	VSConstantBufferStructurePerObject = new VSPerObjectBufferStructSTD;
	PSConstantBufferStructurePerFrame = new PSPerFrameBufferStructSTD;
	PSConstantBufferStructurePerMaterial = new PSPerMaterialBufferStructSTD;

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
	bufferDesc3.ByteWidth = sizeof(VSPerFrameBufferStructSTD);
	bufferDesc3.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc3.CPUAccessFlags = NULL;
	bufferDesc3.MiscFlags = NULL;
	ParentRenderer.Device->CreateBuffer(&bufferDesc3, NULL, &VSPerFrameBuffer);

	D3D11_BUFFER_DESC bufferDesc4;
	ZeroMemory(&bufferDesc4, sizeof(D3D11_BUFFER_DESC));

	bufferDesc4.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc4.ByteWidth = sizeof(PSPerMaterialBufferStructSTD);
	bufferDesc4.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc4.CPUAccessFlags = NULL;
	bufferDesc4.MiscFlags = NULL;
	ParentRenderer.Device->CreateBuffer(&bufferDesc4, NULL, &PSPerMaterialBuffer);


	_Material m;
	m.Emmisive = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
	m.Ambient = XMFLOAT4{ 0.05375f, 0.05f, 0.06625f, 1.0f };
	m.Diffuse = XMFLOAT4{ 0.18275f, 0.17f, 0.22525f, 1.0f };
	m.Specular = XMFLOAT4{ 0.332741f, 0.328634f, 0.346435f, 1.0f };
	m.SpecularPower = 38.4f;
	m.UseTexture = true;
	PSConstantBufferStructurePerMaterial->material = m;
}


D3D11StandardShaderSet::~D3D11StandardShaderSet()
{
	ReleaseCOM(TextureSampler);
	ReleaseCOM(DiffuseMap);
	ReleaseCOM(EnvironmentMap);

	ReleaseCOM(VSPerFrameBuffer);
	ReleaseCOM(VSPerObjectBuffer);
	ReleaseCOM(PSPerFrameBuffer);
	ReleaseCOM(PSPerMaterialBuffer);

	if (VSConstantBufferStructurePerFrame != nullptr)
		delete VSConstantBufferStructurePerFrame;

	if (VSConstantBufferStructurePerObject != nullptr)
		delete VSConstantBufferStructurePerObject;

	if (PSConstantBufferStructurePerFrame != nullptr)
		delete PSConstantBufferStructurePerFrame;

	if (PSConstantBufferStructurePerMaterial != nullptr)
		delete PSConstantBufferStructurePerMaterial;
}

void D3D11StandardShaderSet::Set(D3D11ModelRenderer& renderer)
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	D3D11RenderSystem& RSystem = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle]);
	Vector3f CPosition = RSystem.GetCamera().GetCamPosition();
	CoreSystem& Cs = Engine::MainInstance().SystemsManager.GetCoreSystem();


	ParentRenderer.DeviceContext->RSGetState(&RSPrevState);
	ParentRenderer.DeviceContext->RSSetState(NULL);

	vs.Set();
	ps.Set();

	//SETBUFFERS
	ParentRenderer.DeviceContext->VSSetConstantBuffers(START_SLOT, NUM_BUFFERS, &VSPerObjectBuffer);
	ParentRenderer.DeviceContext->VSSetConstantBuffers(START_SLOT + 1, NUM_BUFFERS, &VSPerFrameBuffer);
	ParentRenderer.DeviceContext->PSSetConstantBuffers(START_SLOT, NUM_BUFFERS, &PSPerFrameBuffer);
	ParentRenderer.DeviceContext->PSSetConstantBuffers(START_SLOT + 1, NUM_BUFFERS, &PSPerMaterialBuffer);
	ParentRenderer.DeviceContext->PSSetShaderResources(0, 1, &DiffuseMap);
	ParentRenderer.DeviceContext->PSSetShaderResources(1, 1, &EnvironmentMap);
	ParentRenderer.DeviceContext->PSSetSamplers(0, 1, &TextureSampler);

	//CAMERA POSITION
	VSConstantBufferStructurePerFrame->CameraWorldPosition = { CPosition.x, CPosition.y, CPosition.z };

	//AMBIENT LIGHT

	//Update per frame buffer
	XMFLOAT4 Ambient;
	Vector3f a = Engine::MainInstance().SystemsManager.GetCoreSystem().GetAmbientColor();
	Ambient.x = a.x / 255.0f; Ambient.y = a.y / 255.0f; Ambient.z = a.z / 255.0f;
	Ambient.w = Engine::MainInstance().SystemsManager.GetCoreSystem().GetAmbientIntensity();
	//Mappen naar 0.0f - 1.0f range
	Ambient.w = Ambient.w / 255.0f;


	Camera& CurrentCamera = RSystem.GetCamera();
	GameObject& Parent = Engine::MainInstance().ObjectsFactory[CurrentCamera.ParentObject];

	XMMATRIX Camera = RSystem.GetWorldMatrix(Parent);
	XMMATRIX View = XMMatrixInverse(&XMMatrixDeterminant(Camera), Camera);

	PSConstantBufferStructurePerFrame->AmbientColor = Ambient;
	
	//DIRECTIONAL LIGHT
	DLPool& DirlightList = const_cast<DLPool&>(Cs.GetDirectionalLightsList());
	int DirlightCount = DirlightList.GetItemInUseCount();

	for (int i = 0; i < DirlightCount; ++i)
	{
		DirectionalLightShaderStruct temp;
		LoadInShaderStruct(DirlightList[i], temp);
		PSConstantBufferStructurePerFrame->DirectionalLights[i] = temp;
	}
	PSConstantBufferStructurePerFrame->DirectionalLightCount = DirlightCount;
	
	//POINT LIGHT
	PLPool& PntlightList = const_cast<PLPool&>(Cs.GetPointLightsList());
	int PntlightCount = PntlightList.GetItemInUseCount();

	for (int i = 0; i < POINT_LIGHT_SHADER_LIMIT; ++i) 
	{
		PointLightShaderStruct temp;
		LoadInShaderStruct(PntlightList[i], temp);
		PSConstantBufferStructurePerFrame->PointLights[i] = temp;
	}
	if (PntlightCount > POINT_LIGHT_SHADER_LIMIT)
		PntlightCount = POINT_LIGHT_SHADER_LIMIT;
	PSConstantBufferStructurePerFrame->PointLightCount = PntlightCount;
	PSConstantBufferStructurePerFrame->CameraWorldPosition = { CPosition.x, CPosition.y, CPosition.z };

	//UPDATE RESOURCES
	ParentRenderer.DeviceContext->UpdateSubresource(PSPerFrameBuffer, 0, NULL, &*PSConstantBufferStructurePerFrame, 0, 0);
	ParentRenderer.DeviceContext->UpdateSubresource(VSPerFrameBuffer, 0, NULL, &*VSConstantBufferStructurePerFrame, 0, 0);
	ParentRenderer.DeviceContext->UpdateSubresource(PSPerMaterialBuffer, 0, NULL, &*PSConstantBufferStructurePerMaterial, 0, 0);
}

void D3D11StandardShaderSet::Update(D3D11ModelRenderer& renderer)
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	
	XMMATRIX W = renderer.GetWorldMatrix();
	XMMATRIX WV = renderer.GetWorldViewMatrix();
	XMMATRIX WVP = renderer.GetWorldViewProjectionMatrix();

	VSConstantBufferStructurePerObject->WorldMatrix = XMMatrixTranspose(W);
	VSConstantBufferStructurePerObject->WorldViewMatrix = XMMatrixTranspose(WV);
	VSConstantBufferStructurePerObject->WorldViewProjectionMatrix = XMMatrixTranspose(WVP);

	ParentRenderer.DeviceContext->UpdateSubresource(VSPerObjectBuffer, 0, NULL, &*VSConstantBufferStructurePerObject, 0, 0);
}

void D3D11StandardShaderSet::RevertState(D3D11ModelRenderer& renderer)
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	ParentRenderer.DeviceContext->RSSetState(RSPrevState);
	RSPrevState = nullptr;
}
