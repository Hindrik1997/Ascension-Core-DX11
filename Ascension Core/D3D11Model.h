//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_D3D11MODEL_H
#define ASCENSION_CORE_D3D11MODEL_H

#include "D3D11Mesh.h"
#include "D3D11Vertex.h"
#include "D3D11ModelRendererShaderSet.h"

class D3D11Model
{
public:
	D3D11Model(D3D11ModelRendererShaderSet& shaderSet, D3D11Mesh& mesh);
	~D3D11Model();
public:
	D3D11ModelRendererShaderSet& ShaderSet;
	D3D11Mesh& Mesh;
public:
	void Set(D3D11ModelRenderer& modelRenderer);
	void Update(D3D11ModelRenderer& modelRenderer);
};

#endif