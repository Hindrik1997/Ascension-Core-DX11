#include "InputStructures.hlslh"
#include "StandardVSOUTPUT.hlslh"
#include "LightStructs.hlslh"

cbuffer cbPerObject : register(b0)
{
	float4x4 WorldMatrix;
	float4x4 WorldViewMatrix;
	float4x4 WorldViewProjectionMatrix;
};

cbuffer cbPerFrame : register(b1)
{
	float3 CameraWorldPosition;
	float padding;
};

VS_OUTPUT main(VS_INPUT IN)
{
	VS_OUTPUT OUTPUT;

	OUTPUT.PSPosition = mul(IN.Position, WorldViewProjectionMatrix);
	OUTPUT.VSPosition = mul(IN.Position.xyz, (float3x3)WorldViewMatrix);
	OUTPUT.WSPosition = mul(IN.Position.xyz, (float3x3)WorldMatrix);

	OUTPUT.TextureCoordinate = IN.TextureCoordinate;
	OUTPUT.WorldSpaceNormal = mul(IN.Normal, (float3x3)WorldMatrix);

	return OUTPUT;
}
