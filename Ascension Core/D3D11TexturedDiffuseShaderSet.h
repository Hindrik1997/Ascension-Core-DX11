#pragma once
#include "D3D11ModelRendererShaderSet.h"
#include "D3D11PSBase.h"
#include "D3D11VSBase.h"

__declspec(align(16)) struct PerObjectBufferStruct
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


class D3D11TexturedDiffuseShaderSet : public D3D11ModelRendererShaderSet
{
public:
	D3D11TexturedDiffuseShaderSet();
	~D3D11TexturedDiffuseShaderSet();

	void Set(D3D11ModelRenderer& renderer);
	void Update(D3D11ModelRenderer& renderer);

private:
	D3D11PixelShaderBase ps;
	D3D11VertexShaderBase vs;

	ID3D11ShaderResourceView* SkyBoxTexture = nullptr;
	ID3D11SamplerState* SkyBoxSampler = nullptr;
	ID3D11Buffer* PerObjectBuffer = nullptr;
	PerObjectBufferStruct* ConstantBufferStructure = nullptr;
	ID3D11RasterizerState* NoCullState = nullptr;
};