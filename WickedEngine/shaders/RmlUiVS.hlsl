// RmlUi vertex shader
// Vertex layout matches Rml::Vertex: position(Vector2f) + colour(RGBA8 premultiplied) + tex_coord(Vector2f)
// The colour is declared as R8G8B8A8_UNORM in the input layout, so it arrives as a normalized float4.

struct VertexInput
{
	float2 pos		: POSITION;
	float4 col		: COLOR0;		// premultiplied alpha, normalized to [0,1]
	float2 uv		: TEXCOORD0;
};

struct VertexOutput
{
	float4 pos : SV_POSITION;
	float4 col : COLOR0;
	float2 uv  : TEXCOORD0;
};

// Constant buffer at slot b0: orthographic projection * translation
cbuffer RmlUiConstants : register(b0)
{
	row_major float4x4 Transform;
};

[RootSignature("RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT), CBV(b0), DescriptorTable(SRV(t0)), DescriptorTable(Sampler(s0))")]
VertexOutput main(VertexInput input)
{
	VertexOutput output;
	output.pos = mul(Transform, float4(input.pos, 0.f, 1.f));
	output.col = input.col;
	output.uv = input.uv;
	return output;
}
