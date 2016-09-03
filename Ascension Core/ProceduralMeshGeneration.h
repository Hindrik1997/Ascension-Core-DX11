#pragma once
#include "Mesh.h"

namespace ProceduralMeshGeneration
{
	//Generates procedural plane
	Mesh GeneratePlane(int verticesWidth, int verticesHeight, float widthVertsDistance = 1, float heightVertsDistance = 1);

	//Generates procedural cone
	Mesh GenerateCone(float height, float radius, int segments);

	//Generates procedural circle
	Mesh GenerateCircle(float radius, int segments);

	//Generates procedural quad using differing width and height
	Mesh GenerateQuad(float width, float height);

	//Generates procedural quad
	Mesh GenerateQuad(float size);

	

};