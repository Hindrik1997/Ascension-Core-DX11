#pragma once
#include "D3D11ModelRendererShaderSet.h"
#include "D3D11PSBase.h"
#include "D3D11VSBase.h"
#include "D3D11LightStructs.h"

__declspec(align(16)) struct _Material
{
	XMFLOAT4 Emmisive;
	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Specular;
	float SpecularPower;
	int UseTexture;
	XMFLOAT2 _PADDING_;

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

__declspec(align(16)) struct VSPerObjectBufferStructSTD
{
	XMMATRIX WorldMatrix;
	XMMATRIX WorldViewMatrix;
	XMMATRIX WorldViewProjectionMatrix;

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

__declspec(align(16)) struct VSPerFrameBufferStructSTD
{
	XMFLOAT3 CameraWorldPosition;
	float padding;

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

__declspec(align(16)) struct PSPerMaterialBufferStructSTD
{
	_Material material;

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

__declspec(align(16)) struct PSPerFrameBufferStructSTD
{
	//Intensity stored in 4th element of this float
	XMFLOAT4 AmbientColor;
	int DirectionalLightCount;
	DirectionalLightShaderStruct DirectionalLights[DIR_LIGHT_SHADER_LIMIT];
	int PointLightCount;
	PointLightShaderStruct PointLights[POINT_LIGHT_SHADER_LIMIT];
	XMFLOAT3 CameraWorldPosition;
	float padding;

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

class D3D11StandardShaderSet : public D3D11ModelRendererShaderSet
{
public:
	D3D11StandardShaderSet(wstring fileName);
	~D3D11StandardShaderSet();

	void Set(D3D11ModelRenderer& renderer);
	void Update(D3D11ModelRenderer& renderer);
	void RevertState(D3D11ModelRenderer& renderer);

private:
	D3D11PixelShaderBase ps;
	D3D11VertexShaderBase vs;

	ID3D11ShaderResourceView* EnvironmentMap = nullptr;
	ID3D11ShaderResourceView* DiffuseMap = nullptr;
	ID3D11SamplerState* TextureSampler = nullptr;

	ID3D11RasterizerState* RSPrevState = nullptr;
	//Buffers

	ID3D11Buffer* VSPerFrameBuffer = nullptr;
	VSPerFrameBufferStructSTD* VSConstantBufferStructurePerFrame = nullptr;

	ID3D11Buffer* VSPerObjectBuffer = nullptr;
	VSPerObjectBufferStructSTD* VSConstantBufferStructurePerObject = nullptr;

	ID3D11Buffer* PSPerMaterialBuffer = nullptr;
	PSPerMaterialBufferStructSTD* PSConstantBufferStructurePerMaterial = nullptr;

	ID3D11Buffer* PSPerFrameBuffer = nullptr;
	PSPerFrameBufferStructSTD* PSConstantBufferStructurePerFrame = nullptr;
};