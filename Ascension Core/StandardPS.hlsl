#include "StandardVSOUTPUT.hlslh"
#include "LightStructs.hlslh"
#include "CommonFunc.hlslh"

cbuffer cbPerFrame : register(b0)
{
	float4 GlobalAmbientLight;
	int DirLightCount;
	DirectionalLight DirectionalLights[DIR_LIGHT_LIMIT];
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
	float3 L = normalize( - DirectionalLights[0].Direction);
	float3 N = normalize(IN.ViewSpaceNormal);
	float4 Light = DirectionalLights[0].Color;
	float3 ViewDirection = normalize( - IN.ViewSpaceViewDirection);
	LightIntensity += Light.w;

	float4 emissive = Material.Emissive;
	float4 ambient = Material.Ambient * GlobalAmbientLight;
	float4 diffuse = Material.Diffuse * DoDiffuse(Light, L, N);
	float4 specular = Material.Specular * DoSpecularBlinnPhong(Light, ViewDirection, L, N, Material.SpecularPower);

	float4 Environment = CubeMap.Sample(TrilinearSampler, IN.ReflectionVector);

	float4 color = {1,1,1,1};

	if (Material.UseTexture)
	{
		color = ColorMap.Sample(TrilinearSampler, IN.TextureCoordinate);
	}

	float4 fragmentColor = (emissive + ambient + diffuse + specular) * color;
	return fragmentColor;
}