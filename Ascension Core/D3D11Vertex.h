//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_D3D11VERTEX_H
#define ASCENSION_CORE_D3D11VERTEX_H

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "ReleaseCOM.h"

using namespace DirectX;

class D3D11Vertex
{
public:
	XMFLOAT3 Position;
	XMFLOAT4 Color;

	D3D11Vertex(float x, float y, float z);
	D3D11Vertex(float x, float y, float z, float r, float g, float b, float a);
	~D3D11Vertex();

	static D3D11_INPUT_ELEMENT_DESC Layout[];
	static int LayoutSize;

};

#endif