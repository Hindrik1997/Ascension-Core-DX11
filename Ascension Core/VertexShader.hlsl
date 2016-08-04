
cbuffer cbPerObject
{
    //WorldViewProjection matrix
    float4x4 WVP;
};




struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;

};


VS_OUTPUT main(float4 pos : POSITION, float4 color : COLOR)
{
    VS_OUTPUT output;
    output.Color = color;
    output.Pos = mul(pos, WVP);
	return output;
}