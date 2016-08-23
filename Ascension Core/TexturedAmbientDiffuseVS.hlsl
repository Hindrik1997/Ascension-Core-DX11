#include "InputStructures.hlslh"
#include "TexturedAmbientDiffuseVSOUTPUT.hlslh"

cbuffer cbPerObject : register(b0)
{
	float4x4 WVP;
};

VS_OUTPUT main(VS_INPUT IN)
{
	VS_OUTPUT output;
	output.TexCoord = IN.TextureCoordinate;
	output.Pos = mul(IN.Position, WVP);
	return output;
}