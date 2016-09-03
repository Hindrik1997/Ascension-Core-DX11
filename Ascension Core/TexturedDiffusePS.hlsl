#include "TexturedDiffuseVSOUTPUT.hlslh"

SamplerState TrilinearSampler;
Texture2D Texture;

float4 main(VS_OUTPUT input) : SV_TARGET
{
	return Texture.Sample(TrilinearSampler, input.TexCoord);
}
