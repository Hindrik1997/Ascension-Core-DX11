#include "SkyBoxVSOUTPUT.hlslh"

SamplerState TrilinearSampler;
TextureCube Skybox;

float4 main(VS_OUTPUT input) : SV_TARGET
{
	return Skybox.Sample(TrilinearSampler, input.TexCoord);
}