#include "Common.hlsli"
#include "Lighting.hlsli"

struct VOut
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
    float4 colour : COLOR;
};

VOut main(VIn input)
{
    VOut output;
    output.position = mul(WVP, float4(input.position, 1));
    output.uv = input.uv;
    
    output.colour = float4(CalculateAllLighting(ambientLightCol.xyz, dirLight, pointLights, float4(input.position, 1), input.normal), 1);
    
    return output;
}