//
//  Camera.cpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#include "Camera.hpp"
#include <cmath>

Camera::Camera()
    : position(simd::make_float3(0, 0, -5)),
      rotation(simd::make_float3(0, 0, 0)) {}

simd::float4x4 Camera::getViewMatrix() const {
    float cx = std::cos(rotation.x), sx = std::sin(rotation.x);
    float cy = std::cos(rotation.y), sy = std::sin(rotation.y);
    float cz = std::cos(rotation.z), sz = std::sin(rotation.z);

    simd::float4 col0 = simd::make_float4(cy * cz, cx * sz + sx * sy * cz, sx * sz - cx * sy * cz, 0);
    simd::float4 col1 = simd::make_float4(-cy * sz, cx * cz - sx * sy * sz, sx * cz + cx * sy * sz, 0);
    simd::float4 col2 = simd::make_float4(sy, -sx * cy, cx * cy, 0);
    simd::float4 col3 = simd::make_float4(-position.x, -position.y, -position.z, 1);

    return simd::float4x4(col0, col1, col2, col3);
}

simd::float4x4 Camera::getProjectionMatrix() const {
    float aspect = 640.0f / 480.0f; // Adjust this based on your window size
    float fovy = 60.0f * (M_PI / 180.0f);
    float near = 0.1f;
    float far = 100.0f;

    float yScale = 1.0f / std::tan(fovy * 0.5f);
    float xScale = yScale / aspect;
    float zRange = far - near;
    float zScale = -(far + near) / zRange;
    float wzScale = -2 * far * near / zRange;

    simd::float4 col0 = simd::make_float4(xScale, 0, 0, 0);
    simd::float4 col1 = simd::make_float4(0, yScale, 0, 0);
    simd::float4 col2 = simd::make_float4(0, 0, zScale, -1);
    simd::float4 col3 = simd::make_float4(0, 0, wzScale, 0);

    return simd::float4x4(col0, col1, col2, col3);
}
