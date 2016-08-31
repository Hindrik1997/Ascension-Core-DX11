#pragma once
#include <DirectXMath.h>

using namespace DirectX;

#define POINT_LIGHT_SHADER_LIMIT 24
#define DIR_LIGHT_SHADER_LIMIT 8

class PointLight;
class DirectionalLight;
class Spotlight;

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
	float  LightRadius;
	XMFLOAT3 Position;
	XMFLOAT4 Color;
	float padding[4];

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

__declspec(align(16)) struct SpotLightShaderStruct
{
	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

void LoadInShaderStruct(PointLight& p, PointLightShaderStruct& ps);
void LoadInShaderStruct(Spotlight& s, SpotLightShaderStruct& ss);
void LoadInShaderStruct(DirectionalLight& d, DirectionalLightShaderStruct& ds);

void LoadInShaderStructToViewSpace(DirectionalLight& d, DirectionalLightShaderStruct& ds, XMMATRIX& ViewMatrix);
void LoadInShaderStructToViewSpace(PointLight& p, PointLightShaderStruct& ps, XMMATRIX& ViewMatrix);
void LoadInShaderStructToViewSpace(Spotlight& s, SpotLightShaderStruct& ss, XMMATRIX& ViewMatrix);