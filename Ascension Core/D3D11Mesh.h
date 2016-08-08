//
// Created by Hindrik Stegenga on 8/1/2016.
//

#ifndef ASCENSION_CORE_D3D11MESH_H
#define ASCENSION_CORE_D3D11MESH_H

#include "ReleaseCOM.h"
#include "D3D11Vertex.h"
#include "D3D11Renderer.h"

#include <vector>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

using std::vector;


class D3D11Mesh
{
public:
	D3D11Mesh(vector<DWORD> indices, vector<D3D11Vertex> vertices);
	~D3D11Mesh();

	void Set();

	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;

	vector<DWORD> Indices;
	vector<D3D11Vertex> Vertices;
};


#endif