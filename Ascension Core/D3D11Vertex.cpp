#include "D3D11Vertex.h"

D3D11_INPUT_ELEMENT_DESC D3D11Vertex::Layout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

int D3D11Vertex::LayoutSize = ARRAYSIZE(D3D11Vertex::Layout);


D3D11Vertex::D3D11Vertex(float x, float y, float z) : Position(x, y, z), Color(1.0f, 1.0f, 1.0f, 1.0f)
{
}

D3D11Vertex::D3D11Vertex(float x, float y, float z, float r, float g, float b, float a) : Position(x, y, z), Color(r, g, b, a)
{
}


D3D11Vertex::~D3D11Vertex()
{
}