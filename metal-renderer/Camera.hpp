//
//  Camera.hpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

// Camera.hpp

#pragma once

#include <simd/simd.h>

class Camera {
public:
    Camera();

    void moveForward(float delta);
    void moveRight(float delta);
    void rotate(float yawDelta, float pitchDelta);

    simd::float4x4 getViewMatrix() const;
    simd::float4x4 getProjectionMatrix() const;

private:
    simd::float3 position;
    float yaw;
    float pitch;

    const float movementSpeed = 1.0f;
    const float mouseSensitivity = 0.004f;

    void updateVectors();
    simd::float3 front;
    simd::float3 right;
    simd::float3 up;
};


