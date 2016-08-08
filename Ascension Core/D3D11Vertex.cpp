#include "D3D11Vertex.h"

D3D11_INPUT_ELEMENT_DESC D3D11Vertex::Layout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

int D3D11Vertex::LayoutSize = ARRAYSIZE(D3D11Vertex::Layout);

D3D11Vertex::D3D11Vertex(Vertex v) : 
	Position(v.Position.x, v.Position.y, v.Position.z, 1.0f),
	UV(v.UV.x, v.UV.y, v.UV.z),
	Normal(v.Normal.x,v.Normal.y, v.Normal.z),
	Color(v.Color.x, v.Color.y, v.Color.z, v.Color.w)
{
}

D3D11Vertex::~D3D11Vertex()
{
}