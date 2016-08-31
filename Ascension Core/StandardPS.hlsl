#include "StandardVSOUTPUT.hlslh"
#include "LightStructs.hlslh"
#include "CommonFunc.hlslh"

cbuffer cbPerFrame : register(b0)
{
	float4 GlobalAmbientLight;
	int DirLightCount;
	DirectionalLight DirectionalLights[DIR_LIGHT_LIMIT];
	int PntLightCount;
	PointLight PointLights[PNT_LIGHT_LIMIT];
};

cbuffer cbPerMaterial : register(b1)
{
	_Material Material;
}

//Lightning calculations in view space!
//LightDirections precalculated on cpu in view space

SamplerState TrilinearSampler;
Texture2D ColorMap : register(t0);
TextureCube CubeMap : register(t1);

float4 main(VS_OUTPUT IN) : SV_TARGET
{
	
	float LightIntensity = 1.0f;
	float3 N = normalize(IN.ViewSpaceNormal);
	float3 ViewDirection = normalize( - IN.ViewSpaceViewDirection);

	float4 emissive = Material.Emissive;
	float4 ambient = Material.Ambient * GlobalAmbientLight;
	float4 diffuse = 0.0f;
	float4 specular = 0.0f;

	
	for (int i = 0; i < DirLightCount; ++i)
	{
		float4 Light = DirectionalLights[i].Color;
		float3 L = normalize(-DirectionalLights[i].Direction);
		if (Light.w > 0)
		{
			LightIntensity += Light.w;
			diffuse += Material.Diffuse * DoDiffuse(Light, L, N);
			specular += Material.Specular * DoSpecularBlinnPhong(Light, ViewDirection, L, N, Material.SpecularPower);
		}
	}
	
	for (int j = 0; j < PntLightCount; ++j)
	{
		float4 Light = PointLights[j].Color;
		float3 L = normalize(PointLights[j].Position - IN.WorldPosition);
		if (Light.w > 0)
		{
			LightIntensity += saturate(1.0f - (length(L) / PointLights[j].Radius));
			diffuse += Material.Diffuse * DoDiffuse(Light, L, N);
			//specular += Material.Specular * DoSpecularBlinnPhong(Light, ViewDirection, L, N, Material.SpecularPower);
		}
	}


	//float4 Environment = CubeMap.Sample(TrilinearSampler, IN.ReflectionVector);

	float4 color = {1,1,1,1};

	if (Material.UseTexture)
	{
		color = ColorMap.Sample(TrilinearSampler, (float2)IN.TextureCoordinate);
	}
	
	

	float4 fragmentColor = (emissive + ambient + (diffuse + specular * LightIntensity)) * color;
	return fragmentColor;
}