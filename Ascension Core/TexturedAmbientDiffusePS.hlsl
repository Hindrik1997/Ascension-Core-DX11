#include "TexturedAmbientDiffuseVSOUTPUT.hlslh"

cbuffer cbPerFrame : register(b0)
{
	float4 Ambient;
};

SamplerState TrilinearSampler;
Texture2D Texture;

float4 main(VS_OUTPUT input) : SV_TARGET
{
	float4 color = Texture.Sample(TrilinearSampler, input.TexCoord);
	color.rgb *= Ambient.rgb * Ambient.a;
	//Ambient.rgb = ambient color
	//Ambient.a = Intensity
	return color;
}
