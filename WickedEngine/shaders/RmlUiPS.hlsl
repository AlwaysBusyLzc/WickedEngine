// RmlUi pixel shader
// Samples the bound texture (if any) and multiplies by the vertex colour.
// RmlUi colours use premultiplied alpha, so the blend state should use
// SRC_BLEND = ONE, DEST_BLEND = INV_SRC_ALPHA for correct results.

struct VertexOutput
{
	float4 pos : SV_POSITION;
	float4 col : COLOR0;
	float2 uv  : TEXCOORD0;
};

Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

[RootSignature("RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT), CBV(b0), DescriptorTable(SRV(t0)), DescriptorTable(Sampler(s0))")]
float4 main(VertexOutput input) : SV_TARGET
{
	return input.col * texture0.Sample(sampler0, input.uv);
}
