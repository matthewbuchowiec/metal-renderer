//
//  Shader.metal
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#include <metal_stdlib>
using namespace metal;

struct VertexIn {
    float3 position [[attribute(0)]];
    float4 color [[attribute(1)]];
};

struct VertexOut {
    float4 position [[position]];
    float4 color;
};

struct Uniforms {
    float4x4 modelViewProjectionMatrix;
};

vertex VertexOut vertexShader(VertexIn in [[stage_in]],
                              constant float4x4 &modelViewProjectionMatrix [[buffer(1)]]) {
    VertexOut out;
    out.position = modelViewProjectionMatrix * float4(in.position, 1.0);
    out.color = in.color;
    return out;
}

fragment float4 fragmentShader(VertexOut in [[stage_in]]) {
    return in.color;
}
