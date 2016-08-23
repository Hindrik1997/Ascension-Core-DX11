#pragma once
#include "D3D11ModelRendererShaderSet.h"
#include "D3D11PSBase.h"
#include "D3D11VSBase.h"
#include "LightStructs.h"

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
	//light list

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

	//Directional light list
	int LightCount;
	DirectionalLightShaderStruct DirectionalLights[LIGHT_COUNT_PS];

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

private:
	D3D11PixelShaderBase ps;
	D3D11VertexShaderBase vs;

	ID3D11ShaderResourceView* Texture = nullptr;
	ID3D11SamplerState* TextureSampler = nullptr;

	//Buffers

	ID3D11Buffer* VSPerFrameBuffer = nullptr;
	VSPerFrameBufferStructSTD* VSConstanBufferStructurePerFrame = nullptr;

	ID3D11Buffer* VSPerObjectBuffer = nullptr;
	VSPerObjectBufferStructSTD* VSConstantBufferStructurePerObject = nullptr;




	ID3D11Buffer* PSPerFrameBuffer = nullptr;
	PSPerFrameBufferStructSTD* PSConstantBufferStructurePerFrame = nullptr;
};