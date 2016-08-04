#include "D3D11Mesh.h"

D3D11Mesh::D3D11Mesh(D3D11Renderer& renderer, vector<DWORD> indices, vector<D3D11Vertex> vertices) : ParentRenderer(renderer), Indices(indices), Vertices(vertices)
{
	D3D11_BUFFER_DESC IndexBufferDesc;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.ByteWidth = static_cast<int>(sizeof(DWORD)) * static_cast<int>(Indices.size());
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA IndexBufferData;
	IndexBufferData.pSysMem = &Indices[0];
	renderer.Device->CreateBuffer(&IndexBufferDesc, &IndexBufferData, &IndexBuffer);

	renderer.DeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	D3D11_BUFFER_DESC VertexBufferDesc;
	ZeroMemory(&VertexBufferDesc, sizeof(VertexBufferDesc));

	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDesc.ByteWidth = static_cast<int>(sizeof(D3D11Vertex)) * static_cast<int>(Vertices.size());
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.CPUAccessFlags = 0;
	VertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA VertexBufferData;
	ZeroMemory(&VertexBufferData, sizeof(VertexBufferData));
	VertexBufferData.pSysMem = &Vertices[0];
	renderer.Device->CreateBuffer(&VertexBufferDesc, &VertexBufferData, &VertexBuffer);
}


D3D11Mesh::~D3D11Mesh()
{
	ReleaseCOM(VertexBuffer);
	ReleaseCOM(IndexBuffer);
}
