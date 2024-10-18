//
//  Shader.metal
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#include <metal_stdlib>
using namespace metal;

struct VertexIn {
    float4 position [[attribute(0)]];
    float4 color [[attribute(1)]];
    float3 normal [[attribute(2)]];
};

struct VertexOut {
    float4 position [[position]];
    float3 normal;
    float3 worldPosition;
};

struct Uniforms {
    float4x4 modelViewProjectionMatrix;
    float4x4 modelMatrix;
    float4x4 normalMatrix;
};

vertex VertexOut vertexShader(VertexIn in [[stage_in]],
                              constant Uniforms &uniforms [[buffer(1)]]) {
    VertexOut out;
    out.position = uniforms.modelViewProjectionMatrix * in.position;
    out.normal = (uniforms.normalMatrix * float4(in.normal, 0.0)).xyz;
    out.worldPosition = (uniforms.modelMatrix * in.position).xyz;
    return out;
}

fragment float4 fragmentShader(VertexOut in [[stage_in]]) {
    float3 lightPosition = float3(5.0, 6.0, 7.0);
    float3 lightColor = float3(1.0, 1.0, 1.0);
    float ambientStrength = 0.1;
    float3 objectColor = float3(0.5, 0.5, 0.5);

    float3 ambient = ambientStrength * lightColor;

    float3 normal = normalize(in.normal);
    float3 lightDir = normalize(lightPosition - in.worldPosition);
    float diff = max(dot(normal, lightDir), 0.0);
    float3 diffuse = diff * lightColor;

    float3 result = (ambient + diffuse) * objectColor;

    return float4(result, 1.0);
}
