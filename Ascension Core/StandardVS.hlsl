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
	float3 LightDirection;
	float2 padding;
};

VS_OUTPUT main(VS_INPUT IN)
{
	VS_OUTPUT output;

	float3 worldPosition = mul(IN.Position, WorldMatrix).xyz;
	float3 incident = normalize(CameraWorldPosition - worldPosition);

	output.Position = mul(IN.Position, WorldViewProjectionMatrix);
	output.TextureCoordinate = IN.TextureCoordinate;
	output.ViewSpaceNormal = normalize(mul((float3x3)WorldViewMatrix, IN.Normal));
	output.ViewSpaceViewDirection = normalize(mul((float3x3)WorldViewMatrix,incident));

	return output;
}