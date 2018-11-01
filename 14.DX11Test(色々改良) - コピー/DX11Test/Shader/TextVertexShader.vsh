struct VS_IN
{
    float4 pos : POSITION0;
	float2 tex : TEXTURE0;
};
 
struct VS_OUT
{
    float4 pos : SV_POSITION;
	float2 tex : TEXTURE0;
};

VS_OUT vs_main( VS_IN input )
{
    VS_OUT output;

    output.pos = input.pos;
    output.tex = input.tex;

    return output;
}