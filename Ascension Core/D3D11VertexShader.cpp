//
// Created by Hindrik Stegenga on 8/1/2016.
//

#include "D3D11VertexShader.h"
#include <chrono>

#define START_SLOT 0
#define NUM_BUFFERS 1

D3D11VertexShader::D3D11VertexShader(D3D11Renderer& renderer, wstring fileName) : ParentRenderer(renderer), FileName(fileName)
{
	D3DReadFileToBlob(FileName.c_str(), &VS_Buffer);
	if (VS_Buffer == nullptr)
		throw "Invalid pixel shader filename!";

	ParentRenderer.Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(PerObjectBufferStruct);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = NULL;
	bufferDesc.MiscFlags = NULL;
	ParentRenderer.Device->CreateInputLayout(D3D11Vertex::Layout, D3D11Vertex::LayoutSize, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &InputLayout);
	ParentRenderer.Device->CreateBuffer(&bufferDesc, NULL, &PerObjectBuffer);
}

void D3D11VertexShader::SetInputLayout(D3D11Mesh& mesh)
{
	unsigned int stride = sizeof(D3D11Vertex);
	unsigned int offset = 0;
	ParentRenderer.DeviceContext->IASetVertexBuffers(START_SLOT, NUM_BUFFERS, &(mesh.VertexBuffer), &stride, &offset);
	ParentRenderer.DeviceContext->IASetInputLayout(InputLayout);
	ParentRenderer.DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void D3D11VertexShader::UpdateConstantBuffer(XMFLOAT4X4 WVP)
{
	ConstantBufferStructure.WVP = XMMatrixTranspose(XMLoadFloat4x4(&WVP));
	ParentRenderer.DeviceContext->UpdateSubresource(PerObjectBuffer, 0, NULL, &ConstantBufferStructure,0,0);
	ParentRenderer.DeviceContext->VSSetConstantBuffers(START_SLOT, NUM_BUFFERS, &PerObjectBuffer);
}

D3D11VertexShader::~D3D11VertexShader()
{
	ReleaseCOM(VS);
	ReleaseCOM(VS_Buffer);
	ReleaseCOM(InputLayout);
	ReleaseCOM(PerObjectBuffer);
}