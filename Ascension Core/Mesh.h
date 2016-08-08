#pragma once
#include "Vertex.h"
#include <vector>

using std::vector;

class Mesh
{
public:
	Mesh();
	Mesh(vector<Vertex> vertices, vector<int> indices);
	
	~Mesh();


	inline int VerticeCount();
	inline int IndiceCount();
public:
	vector<Vertex> Vertices;
	vector<int> Indices;
};

inline int Mesh::IndiceCount() 
{
	return static_cast<int>(Indices.size());
}

inline int Mesh::VerticeCount() 
{
	return static_cast<int>(Vertices.size());
}