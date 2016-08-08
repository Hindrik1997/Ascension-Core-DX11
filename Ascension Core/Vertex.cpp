#include "Vertex.h"


Vertex::Vertex()
{
}


Vertex::~Vertex()
{
}

Vertex::Vertex(Vector3f position, Vector4f color) : Position(position), Color(color)
{
}

Vertex::Vertex(Vector3f position, Vector3f uv, Vector3f normal, Vector4f color) : Position(position), UV(uv), Normal(Normal), Color(color)
{
}

Vertex::Vertex(Vector3f position, Vector3f uv, Vector3f normal) : Position(position), UV(uv), Normal(Normal)
{
}

Vertex::Vertex(Vector3f position, Vector3f uv) : Position(position), UV(uv)
{
}

Vertex::Vertex(Vector3f position) : Position(position)
{
}

Vertex::Vertex(float pos_x, float pos_y, float pos_z, float uv_u, float uv_v, float uv_w, float normal_x, float normal_y, float normal_z, float color_r, float color_g, float color_b, float color_a) :
	Position(pos_x, pos_y, pos_z),
	UV(uv_u, uv_v, uv_w),
	Normal(normal_x, normal_y, normal_z),
	Color(color_r, color_g, color_b, color_a)
{
}

Vertex::Vertex(float pos_x, float pos_y, float pos_z, float uv_u, float uv_v, float uv_w, float normal_x, float normal_y, float normal_z) :
	Position(pos_x, pos_y, pos_z),
	UV(uv_u, uv_v, uv_w),
	Normal(normal_x, normal_y, normal_z)
{
}

Vertex::Vertex(float pos_x, float pos_y, float pos_z, float color_r, float color_g, float color_b, float color_a) :
	Position(pos_x, pos_y, pos_z),
	Color(color_r, color_g, color_b, color_a)
{
}

Vertex::Vertex(float pos_x, float pos_y, float pos_z, float uv_u, float uv_v, float uv_w) :
	Position(pos_x, pos_y, pos_z),
	UV(uv_u, uv_v, uv_w)
{
}

Vertex::Vertex(float pos_x, float pos_y, float pos_z) : 
	Position(pos_x, pos_y, pos_z)
{
}
