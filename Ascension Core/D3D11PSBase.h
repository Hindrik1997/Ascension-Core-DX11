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

class D3D11PixelShaderBase
{
public:
	D3D11PixelShaderBase(wstring fileName);
	~D3D11PixelShaderBase();
public:
	void Set();
public:
	ID3D11PixelShader* PS = nullptr;
	ID3DBlob* PS_Buffer = nullptr;
	wstring FileName;
};

#endif