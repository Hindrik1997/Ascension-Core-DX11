#include "InputStructures.hlslh"
#include "TexturedDiffuseVSOUTPUT.hlslh"

cbuffer cbPerObject
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
