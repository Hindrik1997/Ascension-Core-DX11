#pragma once
#include <DirectXMath.h>
using namespace DirectX;

#define LIGHT_COUNT_PS 8
#define LIGHT_COUNT_VS 24
#define LIGHT_COUNT_DIRECTIONAL_PS 4

//Intensity is in Color.w
struct DirectionalLightShaderStruct
{
	XMFLOAT3 Direction;
	XMFLOAT4 Color;
};

//Intensity is in Color.w
struct PointLightShaderStruct
{
	XMFLOAT3 Position;
	XMFLOAT4 Color;
	float  LightRadius;
};