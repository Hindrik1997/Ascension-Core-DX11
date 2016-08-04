//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_D3D11VERTEXSHADER_H
#define ASCENSION_CORE_D3D11VERTEXSHADER_H


#include <memory>
#include <string>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include "ReleaseCOM.h"
#include "D3D11Renderer.h"
#include "D3D11Vertex.h"
#include "D3D11Mesh.h"

using std::wstring;
using std::unique_ptr;

struct PerObjectBufferStruct
{
	XMMATRIX WVP;
};

class D3D11VertexShader
{
public:
	D3D11VertexShader(D3D11Renderer& renderer, wstring fileName);
	~D3D11VertexShader();
public:
	inline void SetShader();
	void SetInputLayout(D3D11Mesh& mesh);
	void UpdateConstantBuffer(XMFLOAT4X4 WVP);
public:
	const D3D11Renderer& ParentRenderer;
	ID3D11Buffer* PerObjectBuffer = nullptr;
	PerObjectBufferStruct StructBuffer;
	ID3D11InputLayout* InputLayout = nullptr;
	ID3D11VertexShader* VS = nullptr;
	ID3DBlob* VS_Buffer = nullptr;
	wstring FileName;
};

inline void D3D11VertexShader::SetShader()
{
	ParentRenderer.DeviceContext->VSSetShader(VS, 0, 0);
}

#endif