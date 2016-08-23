#include "StandardVSOUTPUT.hlslh"
#include "LightStructs.hlslh"



cbuffer cbPerFrame : register(b0)
{
	float4 Ambient;
	int lightCount;
	DirectionalLight DirectionalLights[LIGHT_COUNT_PS];
};

SamplerState TrilinearSampler;
Texture2D Texture;

float4 main(VS_OUTPUT input) : SV_TARGET
{
	float4 color = Texture.Sample(TrilinearSampler, input.TextureCoordinate);
	color.rgb *= Ambient.rgb * Ambient.a;
	//Ambient.rgb = ambient color
	//Ambient.a = Intensity

	float3 diffuse = (float3)0;

	for (int i = 0; i < lightCount; ++i)
	{
		float3 lightDir = normalize(- DirectionalLights[i].Direction);
		float3 normal = normalize(input.ViewSpaceNormal);
		
		float n_dot_l = dot(lightDir, normal);

		if (n_dot_l > 0)
		{
			diffuse += DirectionalLights[i].Color.rgb * DirectionalLights[i].Color.a * n_dot_l * color.rgb;
		}

	}

	return color + float4(diffuse, 0.0f);
}