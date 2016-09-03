#include "InputStructures.hlslh"
#include "SkyBoxVSOUTPUT.hlslh"

cbuffer cbPerObject
{
	//WorldViewProjection matrix
	float4x4 WVP;
};

VS_OUTPUT main(VS_INPUT IN)
{
	VS_OUTPUT output;
	output.TexCoord = IN.Position;
	output.Pos = mul(IN.Position, WVP).xyww;
	return output;
}
