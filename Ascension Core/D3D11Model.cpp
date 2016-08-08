//
// Created by Hindrik Stegenga on 7/23/2016.
//

#include "D3D11Model.h"

D3D11Model::D3D11Model(D3D11ModelRendererShaderSet & shaderSet, D3D11Mesh & mesh) : ShaderSet(shaderSet), Mesh(mesh)
{
}

D3D11Model::~D3D11Model()
{
}

void D3D11Model::Set(D3D11ModelRenderer& modelRenderer)
{
	Mesh.Set();
	ShaderSet.Set(modelRenderer);
}

void D3D11Model::Update(D3D11ModelRenderer& modelRenderer)
{
	ShaderSet.Update(modelRenderer);
}
