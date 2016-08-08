#include "D3D11Mesh.h"
#include "D3D11RenderSystem.h"
#include "Engine.h"

#define START_SLOT 0
#define NUM_BUFFERS 1

D3D11Mesh::D3D11Mesh(vector<DWORD> indices, vector<D3D11Vertex> vertices) : Indices(indices), Vertices(vertices)
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;

	//IndexBuffer
	D3D11_BUFFER_DESC IndexBufferDesc;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.ByteWidth = static_cast<int>(sizeof(DWORD)) * static_cast<int>(Indices.size());
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA IndexBufferData;
	IndexBufferData.pSysMem = &Indices[0];
	ParentRenderer.Device->CreateBuffer(&IndexBufferDesc, &IndexBufferData, &IndexBuffer);

	ParentRenderer.DeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//VertexBuffer
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
	ParentRenderer.Device->CreateBuffer(&VertexBufferDesc, &VertexBufferData, &VertexBuffer);
}


D3D11Mesh::~D3D11Mesh()
{
	ReleaseCOM(VertexBuffer);
	ReleaseCOM(IndexBuffer);
}

void D3D11Mesh::Set()
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;
	unsigned int stride = sizeof(D3D11Vertex);
	unsigned int offset = 0;
	ParentRenderer.DeviceContext->IASetVertexBuffers(START_SLOT, NUM_BUFFERS, &(VertexBuffer), &stride, &offset);
	ParentRenderer.DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
