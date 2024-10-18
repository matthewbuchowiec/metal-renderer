//
//  Shader.metal
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#include <metal_stdlib>
using namespace metal;

struct VertexIn {
    float4 position [[attribute(0)]];  // Changed from float3 to float4
    float4 color [[attribute(1)]];
    float3 normal [[attribute(2)]];
};

struct VertexOut {
    float4 position [[position]];
    float4 color;
    float3 normal;
};

struct Uniforms {
    float4x4 modelViewProjectionMatrix;
    float4x4 normalMatrix;
};

vertex VertexOut vertexShader(VertexIn in [[stage_in]],
                              constant Uniforms &uniforms [[buffer(1)]]) {
    VertexOut out;
    out.position = uniforms.modelViewProjectionMatrix * in.position;
    out.color = in.color;
    out.normal = (uniforms.normalMatrix * float4(in.normal, 0.0)).xyz;
    return out;
}

fragment float4 fragmentShader(VertexOut in [[stage_in]]) {
    float3 lightDirection = normalize(float3(1.0, 1.0, 1.0));
    float3 normal = normalize(in.normal);
    float diffuseIntensity = max(0.0, dot(normal, lightDirection));
    return float4(in.color.rgb * diffuseIntensity, in.color.a);
}
