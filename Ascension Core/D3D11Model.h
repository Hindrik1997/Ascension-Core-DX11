//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_D3D11MODEL_H
#define ASCENSION_CORE_D3D11MODEL_H

#include "D3D11Mesh.h"
#include "D3D11Vertex.h"
#include "D3D11VertexShader.h"
#include "D3D11PixelShader.h"

class D3D11Model
{
public:
	D3D11Model(D3D11VertexShader& vertexShader, D3D11PixelShader& pixelShader, D3D11Mesh& mesh);
	~D3D11Model();
public:
	D3D11VertexShader& VertexShader;
	D3D11PixelShader& PixelShader;
	D3D11Mesh& Mesh;
public:
	void Set() const;
};

#endif