#include "D3D11LightStructs.h"
#include "DirectionalLight.h"
#include "PointLight.h"


void LoadInShaderStruct(PointLight & p, PointLightShaderStruct & ps)
{
	ps.Position = XMFLOAT3(p.GetPosition().x, p.GetPosition().y, p.GetPosition().z);
	ps.Color = XMFLOAT4(p.GetColor().x / 255, p.GetColor().y / 255, p.GetColor().z / 255, p.GetIntensity());
	ps.LightRadius = p.GetRadius();
}

void LoadInShaderStruct(Spotlight & s, SpotLightShaderStruct & ss)
{
	throw "NOT IMPLEMENTED";
}

void LoadInShaderStruct(DirectionalLight & d, DirectionalLightShaderStruct & ds)
{
	ds.Direction = XMFLOAT3(d.GetDirection().x, d.GetDirection().y, d.GetDirection().z);
	ds.Color = XMFLOAT4(d.GetColor().x / 255, d.GetColor().y / 255, d.GetColor().z / 255,d.GetIntensity());
}

void LoadInShaderStructToViewSpace(DirectionalLight & d, DirectionalLightShaderStruct & ds, XMMATRIX& ViewMatrix)
{
	ds.Direction = XMFLOAT3(d.GetDirection().x, d.GetDirection().y, d.GetDirection().z);
	XMVECTOR resultDir = XMVector3Transform(XMLoadFloat3(&ds.Direction), XMMatrixTranspose(ViewMatrix));
	XMStoreFloat3(&ds.Direction, resultDir);
	ds.Color = XMFLOAT4(d.GetColor().x / 255, d.GetColor().y / 255, d.GetColor().z / 255, d.GetIntensity());
}

void LoadInShaderStructToViewSpace(PointLight & p, PointLightShaderStruct & ps, XMMATRIX& ViewMatrix)
{
	ps.Position = XMFLOAT3(p.GetPosition().x, p.GetPosition().y, p.GetPosition().z);
	XMVECTOR resultDir = XMVector3Transform(XMLoadFloat3(&ps.Position), XMMatrixTranspose(ViewMatrix));
	XMStoreFloat3(&ps.Position, resultDir);
	ps.Color = XMFLOAT4(p.GetColor().x / 255, p.GetColor().y / 255, p.GetColor().z / 255, p.GetIntensity());
	ps.LightRadius = p.GetRadius();
}

void LoadInShaderStructToViewSpace(Spotlight & s, SpotLightShaderStruct & ss, XMMATRIX& ViewMatrix)
{
	throw "NOT IMPLEMENTED";
	/*
	ds.Direction = XMFLOAT3(s.GetDirection().x, s.GetDirection().y, s.GetDirection().z);
	XMVECTOR resultDir = XMVector3Transform(XMLoadFloat3(&ds.Direction), XMMatrixTranspose(ViewMatrix));
	XMStoreFloat3(&ds.Direction, resultDir);
	ds.Color = XMFLOAT4(s.GetColor().x / 255, s.GetColor().y / 255, s.GetColor().z / 255, s.GetIntensity());
	*/
}