#pragma once
#include <DirectXMath.h>
using namespace DirectX;

#define LIGHT_COUNT_PS 8
#define LIGHT_COUNT_VS 24
#define LIGHT_COUNT_DIRECTIONAL_PS 4

__declspec(align(16)) struct DirectionalLightShaderStruct
{
	float padding;
	XMFLOAT3 Direction;
	XMFLOAT4 Color;

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

__declspec(align(16)) struct PointLightShaderStruct
{
	XMFLOAT3 Position;
	float  LightRadius;
	XMFLOAT4 Color;

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

__declspec(align(16)) struct _Material
{
	XMFLOAT4 Emmisive;
	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Specular;
	float SpecularPower;
	int UseTexture;
	XMFLOAT2 _PADDING_;

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};