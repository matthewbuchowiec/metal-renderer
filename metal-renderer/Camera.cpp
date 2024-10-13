//
//  Camera.cpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#include "Camera.hpp"
#include <cmath>
#include <iostream>

Camera::Camera()
    : position(simd::make_float3(0, 0, 3)),
      yaw(-M_PI_2),
      pitch(0) {
    updateVectors();
}

void Camera::moveForward(float delta) {
    position += front * delta * movementSpeed;
}

void Camera::moveRight(float delta) {
    position += right * delta * movementSpeed;
}

void Camera::rotate(float yawDelta, float pitchDelta) {
    yaw += yawDelta * mouseSensitivity;
    pitch += pitchDelta * mouseSensitivity;
    
    yaw = std::fmod(yaw, M_PI * 2);
    if (yaw < 0) yaw += M_PI * 2;

    const float pitchLimit = M_PI_2 - 0.01f;
    if (pitch > pitchLimit) pitch = pitchLimit;
    if (pitch < -pitchLimit) pitch = -pitchLimit;

    updateVectors();
}


void Camera::updateVectors() {
    front = simd::normalize(simd::make_float3(
        cos(yaw) * cos(pitch),
        sin(pitch),
        sin(yaw) * cos(pitch)
    ));

    right = simd::normalize(simd::cross(front, simd::make_float3(0, 1, 0)));
    up = simd::normalize(simd::cross(right, front));
}

simd::float4x4 Camera::getViewMatrix() const {
    simd::float3 center = position + front;
    simd::float3 f = simd::normalize(center - position);
    simd::float3 s = simd::normalize(simd::cross(f, up));
    simd::float3 u = simd::cross(s, f);

    return simd::float4x4(
        simd::make_float4(s.x, u.x, -f.x, 0),
        simd::make_float4(s.y, u.y, -f.y, 0),
        simd::make_float4(s.z, u.z, -f.z, 0),
        simd::make_float4(-simd::dot(s, position), -simd::dot(u, position), simd::dot(f, position), 1)
    );
}

simd::float4x4 Camera::getProjectionMatrix() const {
    float aspect = 1920.0f / 1080.0f;
    float fovy = 80.0f * (M_PI / 180.0f);
    float near = 0.1f;
    float far = 100.0f;

    float yScale = 1.0f / std::tan(fovy * 0.5f);
    float xScale = yScale / aspect;
    float zRange = far - near;
    float zScale = -(far + near) / zRange;
    float wzScale = -2 * far * near / zRange;

    return simd::float4x4(
        simd::make_float4(xScale, 0, 0, 0),
        simd::make_float4(0, yScale, 0, 0),
        simd::make_float4(0, 0, zScale, -1),
        simd::make_float4(0, 0, wzScale, 0)
    );
}

