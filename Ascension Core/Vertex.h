#pragma once
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

class Vertex
{
public:
	Vertex();
	~Vertex();
	
	Vertex(Vector3f position, Vector4f color);
	Vertex(Vector3f position, Vector3f uv, Vector3f normal, Vector4f color);
	Vertex(Vector3f position, Vector3f uv, Vector3f normal);
	Vertex(Vector3f position, Vector3f uv);
	Vertex(Vector3f position);

	Vertex(float pos_x, float pos_y, float pos_z, float uv_u, float uv_v, float uv_w, float normal_x, float normal_y, float normal_z, float color_r, float color_g, float color_b, float color_a);
	Vertex(float pos_x, float pos_y, float pos_z, float uv_u, float uv_v, float uv_w, float normal_x, float normal_y, float normal_z);
	Vertex(float pos_x, float pos_y, float pos_z, float color_r, float color_g, float color_b, float color_a);
	Vertex(float pos_x, float pos_y, float pos_z, float uv_u, float uv_v, float uv_w);
	Vertex(float pos_x, float pos_y, float pos_z);

public:
	 Vector3f Position;
	 Vector3f UV;
	 Vector3f Normal;
	 Vector4f Color;
};

