
Texture2D albedo : register(t0);
SamplerState samplerState : register(s0);

struct Input
{
	float4 pos : SV_POSITION;
	float4 worldPos : POSITION;
	float4 texCoord : TEXCOORD;
	float4 normal : NORMAL;
	float4 camPos : CAMPOS;
	float4 tangent : TANGENT;
	float4 bitangent : BITANGENT;
};


float4 main(Input input) : SV_TARGET
{
	return albedo.Sample(samplerState, float2(input.texCoord.x, input.texCoord.y));
}