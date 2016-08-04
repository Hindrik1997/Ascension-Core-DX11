//
// Created by Hindrik Stegenga on 7/23/2016.
//

#include "D3D11Model.h"


D3D11Model::D3D11Model(D3D11VertexShader& vertexShader, D3D11PixelShader& pixelShader, D3D11Mesh& mesh) : VertexShader(vertexShader), PixelShader(pixelShader), Mesh(mesh)
{
}


D3D11Model::~D3D11Model()
{
}

void D3D11Model::Set() const
{
	VertexShader.SetShader();
	PixelShader.SetShader();
	VertexShader.SetInputLayout(Mesh);
}