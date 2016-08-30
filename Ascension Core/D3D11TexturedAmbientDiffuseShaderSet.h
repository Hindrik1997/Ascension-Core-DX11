#pragma once
#include "D3D11ModelRendererShaderSet.h"
#include "D3D11PSBase.h"
#include "D3D11VSBase.h"

__declspec(align(16)) struct PerObjectBufferStructTAD
{
	XMMATRIX WVP;

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

__declspec(align(16)) struct PerFrameBufferStructTAD 
{
	//Intensity stored in 4th element of this float
	XMFLOAT4 AmbientColor;

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

class D3D11TexturedAmbientDiffuseShaderSet : public D3D11ModelRendererShaderSet
{
public:
	D3D11TexturedAmbientDiffuseShaderSet(wstring fileName);
	~D3D11TexturedAmbientDiffuseShaderSet();

	void Set(D3D11ModelRenderer& renderer);
	void Update(D3D11ModelRenderer& renderer);
	void RevertState(D3D11ModelRenderer& renderer);
private:
	D3D11PixelShaderBase ps;
	D3D11VertexShaderBase vs;

	ID3D11ShaderResourceView* Texture = nullptr;
	ID3D11SamplerState* TextureSampler = nullptr;
	ID3D11Buffer* PerObjectBuffer = nullptr;
	PerObjectBufferStructTAD* ConstantBufferStructurePerObject = nullptr;

	ID3D11Buffer* PerFrameBuffer = nullptr;
	PerFrameBufferStructTAD* ConstantBufferStructurePerFrame = nullptr;

	ID3D11RasterizerState* RSPrevState = nullptr;
};