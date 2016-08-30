#include "Mesh.h"



Mesh::Mesh()
{
}

Mesh::Mesh(vector<Vertex> vertices, vector<int> indices) : Vertices(vertices), Indices(indices)
{
}


Mesh::~Mesh()
{
}

void Mesh::ReverseWindingOrder()
{
	for (size_t i = 0; i < IndiceCount(); i += 3)
	{
		int second;
		second = Indices[i + 1];
		Indices[i + 1] = Indices[i + 2];
		Indices[i + 2] = second;
	}
}

void Mesh::GenerateNormals()
{
	for (size_t i = 0; i < IndiceCount(); i += 3)
	{
		Vertex p1 = Vertices[Indices[i]];
		Vertex p2 = Vertices[Indices[i + 1]];
		Vertex p3 = Vertices[Indices[i + 2]];

		Vector3f vp1 = p1.Position;
		Vector3f vp2 = p2.Position;
		Vector3f vp3 = p3.Position;

		Vector3f vec1 = vp1 - vp2;
		Vector3f vec2 = vp3 - vp1;
		Vector3f Normal = CrossProduct(vec1, vec2);

		Vector3f n1 = p1.Normal;
		Vector3f n2 = p2.Normal;
		Vector3f n3 = p3.Normal;

		n1 += Normal;
		n2 += Normal;
		n3 += Normal;

		n1.Normalize();
		n2.Normalize();
		n3.Normalize();

		Vertices[Indices[i]].Normal = n1;
		Vertices[Indices[i + 1]].Normal = n2;
		Vertices[Indices[i + 2]].Normal = n3;
	}
}