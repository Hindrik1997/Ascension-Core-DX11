#include "InputStructures.hlslh"
#include "StandardVSOUTPUT.hlslh"
#include "LightStructs.hlslh"

cbuffer cbPerObject : register(b0)
{
	float4x4 WorldMatrix;
	float4x4 WorldViewMatrix;
	float4x4 WorldViewProjectionMatrix;
};



VS_OUTPUT main(VS_INPUT IN)
{
	VS_OUTPUT output;
	output.TextureCoordinate = IN.TextureCoordinate;
	output.Position = mul(IN.Position, WorldViewProjectionMatrix);
	output.ViewSpacePosition = mul(IN.Position, WorldViewMatrix);

	output.ViewSpaceNormal = mul((float3x3)WorldViewMatrix, IN.Normal);
	output.ViewSpaceBiNormal = mul((float3x3)WorldViewMatrix, IN.BiNormal);
	output.ViewSpaceTangent = mul((float3x3)WorldViewMatrix, IN.Tangent);

	return output;
}