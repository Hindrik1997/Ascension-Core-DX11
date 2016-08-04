//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_D3D11PIXELSHADER_H
#define ASCENSION_CORE_D3D11PIXELSHADER_H

#include <string>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include "ReleaseCOM.h"
#include "D3D11Renderer.h"

class D3D11PixelShader
{
public:
	D3D11PixelShader(D3D11Renderer& renderer, wstring fileName);
	~D3D11PixelShader();
public:
	inline void SetShader();
public:
	const D3D11Renderer& ParentRenderer;
	ID3D11PixelShader* PS = nullptr;
	ID3DBlob* PS_Buffer = nullptr;
	wstring FileName;
};

inline void D3D11PixelShader::SetShader()
{
	ParentRenderer.DeviceContext->PSSetShader(PS, 0, 0);
}

#endif