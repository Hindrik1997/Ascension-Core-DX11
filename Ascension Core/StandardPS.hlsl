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
	float3 CameraWorldPosition;
	float padding;
};

static const float Glossines = 0.4f;

cbuffer cbPerMaterial : register(b1)
{
	_Material Material;
}

SamplerState Sampler;
Texture2D ColorMap : register(t0);
Texture2D RoughnessMap : register(t1);

float4 main(VS_OUTPUT IN) : SV_TARGET
{

	float3 NativeColor = ColorMap.Sample(Sampler, IN.TextureCoordinate.xy).xyz;

	float3 N = normalize(IN.WorldSpaceNormal);
	float3 V = normalize(CameraWorldPosition - IN.WSPosition);

	float3 Ambient = GlobalAmbientLight.rgb * GlobalAmbientLight.a;
	float3 Diffuse = 0;
	float3 Specular = 0;

	for (int i = 0; i < DirLightCount; ++i)
	{
		if (DirectionalLights[i].Color.a <= 0.0f)
			continue;

		float3 L = normalize(-DirectionalLights[i].Direction);
		float Angle = dot(L,N);
		Angle = Angle * 0.5f + 0.5f; //Remappen voor alle hoeken
		
		float3 R = normalize(2 * Angle * N - L);
		float RdotV = dot(R,V);
		
		
		float SpecularPower = exp2(10 * (1.0f - Glossines) + 1);
		SpecularPower = 25.0f;
		float3 Lspec = max(0, pow(abs(RdotV), SpecularPower));

		float3 Ldiff = max(0, DirectionalLights[i].Color.rgb * DirectionalLights[i].Color.a * Angle - (Lspec * DirectionalLights[i].Color.a));


		Diffuse += Ldiff;
		Specular += Lspec;
	}

	
	for (int j = 0; j < PntLightCount; ++j)
	{
		if (PointLights[j].Color.a <= 0.0f)
			continue;
		float3 L = normalize(- PointLights[j].Position - IN.WSPosition);
		float Attenuation = saturate(1.0f - (length(L) / PointLights[j].Radius));
		
		if (Attenuation <= 0.0f)
			continue;

		float Angle = dot(L, N);
		Angle = Angle * 0.5f + 0.5f; //Remappen voor alle hoeken

		float3 R = normalize(2 * Angle * N - L);
		float RdotV = dot(R, V);

		float SpecularPower = exp2(10 * (1.0f - Glossines) + 1);
		float3 Lspec = max(0, pow(abs(RdotV), SpecularPower)) * Attenuation;

		float3 Ldiff = max(0, PointLights[j].Color.rgb * (PointLights[j].Color.a  * Attenuation)* Angle - (Lspec * PointLights[j].Color.a * Attenuation) );


		Diffuse += Ldiff;
		Specular += Lspec;
	}
	


	
	float4 OUT = 0;
	OUT.rgb = NativeColor * (Ambient + Diffuse) + Specular;
	OUT.a = 1;
	return OUT;
}
