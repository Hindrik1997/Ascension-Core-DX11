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
#include "VertexShaderBase.h"

using std::wstring;
using std::unique_ptr;

//typedef void(*BufferDeleterFncptr)(void* ptr);

class D3D11VertexShaderBase
{
public:
	D3D11VertexShaderBase(wstring fileName);
	~D3D11VertexShaderBase();
public:
	void Set();
	void SetInputLayout();
public:
	ID3D11InputLayout* InputLayout = nullptr;
	ID3D11VertexShader* VS = nullptr;
	ID3DBlob* VS_Buffer = nullptr;
	wstring FileName;
};

#endif