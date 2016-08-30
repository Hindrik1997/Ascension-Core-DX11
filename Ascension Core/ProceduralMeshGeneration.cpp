#include "ProceduralMeshGeneration.h"

double pi = 3.1415926535897;
double two_pi = pi * 2;

namespace ProceduralMeshGeneration 
{
	Mesh GeneratePlane(int verticesWidth, int verticesHeight, float widthVertsDistance, float heightVertsDistance)
	{
		Vector2f Dimensions = Vector2f(verticesWidth, verticesHeight);
		Vector3f* Vertices = new Vector3f[Dimensions.x * Dimensions.y];
		Vector3f* UVWS = new Vector3f[Dimensions.x * Dimensions.y];
		vector<int> Triangles;

		int offsetWidth = -1 * (Dimensions.x * widthVertsDistance) / 2;
		int offsetHeight = -1 * (Dimensions.y * heightVertsDistance) / 2;

		float xStep = 1.0f / Dimensions.x;
		float yStep = 1.0f / Dimensions.y;



		for (int xv = 0; xv < verticesWidth; ++xv)
		{
			for (int yv = 0; yv < verticesHeight; ++yv)
			{
				//sin(xv * widthVertsDistance) * cos(yv * heightVertsDistance),
				Vertices[static_cast<int>(Dimensions.x) * xv + yv] = Vector3f(offsetWidth + xv * widthVertsDistance, sin(xv * widthVertsDistance) * cos(yv * heightVertsDistance), offsetHeight + yv * heightVertsDistance);
				UVWS[static_cast<int>(Dimensions.x) * xv + yv] = Vector3f(xv * xStep, yv * yStep, 0.0f);
			}
		}

		for (int x = 0; x < Dimensions.x - 1; ++x)
		{
			for (int y = 0; y < Dimensions.y - 1; ++y)
			{
				Triangles.push_back(Dimensions.x * x + 1 + y);
				Triangles.push_back(Dimensions.x * x + Dimensions.x + 1 + y);
				Triangles.push_back(Dimensions.x * x + y);

				Triangles.push_back(Dimensions.x * x + y);
				Triangles.push_back(Dimensions.x * x + Dimensions.x + 1 + y);
				Triangles.push_back(Dimensions.x * x + Dimensions.x + y);
			}
		}


		//Copy to vectors

		vector<Vertex> verts;

		for (long i = 0; i < Dimensions.x * Dimensions.y; ++i)
		{
			Vector3f pos, uvw;
			pos = Vertices[i];
			uvw = UVWS[i];
			verts.push_back(Vertex(pos, uvw));
		}

		delete[] Vertices;
		delete[] UVWS;

		//Create Mesh
		Mesh m = Mesh(verts, Triangles);
		m.GenerateNormals();
		return m;
	}

	Mesh GenerateCone(float height, float radius, int segments)
	{
		Mesh mesh;
		float angleInc = two_pi / segments;

		Vertex base(0, -height/2, 0);
		Vertex top(0, height/2, 0);

		mesh.Vertices.push_back(base);
		mesh.Vertices.push_back(top);

		for (int i = 0; i < segments; ++i)
		{
			float angle = angleInc * i;

			Vector3f pos;
			pos.x = cos(angle);
			pos.z = sin(angle);
			Vertex v(pos * radius);
			v.Position.y = -height / 2;
			mesh.Vertices.push_back(v);

		}

		for (int i = 0; i < segments - 1; ++i)
		{
				mesh.Indices.push_back(0);
				mesh.Indices.push_back(i + 2);
				mesh.Indices.push_back(i + 3);
		}

		mesh.Indices.push_back(0);
		mesh.Indices.push_back(segments + 1);
		mesh.Indices.push_back(2);

		for (int i = 0; i < segments - 1; ++i)
		{
			mesh.Indices.push_back(1);
			mesh.Indices.push_back(i + 3);
			mesh.Indices.push_back(i + 2);
		}

		mesh.Indices.push_back(1);
		mesh.Indices.push_back(2);
		mesh.Indices.push_back(segments + 1);

		mesh.GenerateNormals();
		return mesh;
	}

	Mesh GenerateCircle(float radius, int segments)
	{
		Mesh mesh;
		float angleInc = two_pi / segments;

		Vertex base;

		mesh.Vertices.push_back(base);

		for (int i = 0; i < segments; ++i)
		{
			float angle = angleInc * i;

			Vector3f pos;
			pos.x = cos(angle);
			pos.z = sin(angle);
			Vertex v(pos * radius);
			mesh.Vertices.push_back(v);

		}

		for (int i = 0; i < segments - 1; ++i)
		{
			mesh.Indices.push_back(0);
			mesh.Indices.push_back(i + 2);
			mesh.Indices.push_back(i + 1);
		}

		mesh.Indices.push_back(0);
		mesh.Indices.push_back(1);
		mesh.Indices.push_back(segments);

		mesh.GenerateNormals();
		return mesh;
	}

	Mesh GenerateQuad(float width, float height)
	{
		Mesh mesh;

		float hHeight = height / 2;
		float hWidth = width / 2;

		Vertex v1, v2, v3, v4;
		v2.Position = Vector3f(-hWidth, 0, hHeight);	v2.UVW = Vector3f(0, 1, 0);
		v3.Position = Vector3f(hWidth, 0, hHeight);		v3.UVW = Vector3f(1, 1, 0);
		v1.Position = Vector3f(-hWidth, 0, -hHeight);	v1.UVW = Vector3f(0, 0, 0);
		v4.Position = Vector3f(hWidth, 0, -hHeight);	v4.UVW = Vector3f(1, 0, 1);

		mesh.Vertices.push_back(v1);
		mesh.Vertices.push_back(v2);
		mesh.Vertices.push_back(v3);
		mesh.Vertices.push_back(v4);

		int indices[6];
		indices[0] = 1;
		indices[1] = 2;
		indices[2] = 0;

		indices[3] = 0;
		indices[4] = 2;
		indices[5] = 3;


		for (int i = 0; i < 6; ++i)
		{
			mesh.Indices.push_back(indices[i]);
		}

		mesh.GenerateNormals();
		return mesh;
	}

	Mesh GenerateQuad(float size)
	{
		return GenerateQuad(size,size);
	}

}

