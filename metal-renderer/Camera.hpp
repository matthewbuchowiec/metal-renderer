//
//  Camera.hpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#pragma once

#include <simd/simd.h>

class Camera {
public:
    Camera();

    void setPosition(const simd::float3& position) { this->position = position; }
    void setRotation(const simd::float3& rotation) { this->rotation = rotation; }

    simd::float4x4 getViewMatrix() const;
    simd::float4x4 getProjectionMatrix() const;

private:
    simd::float3 position;
    simd::float3 rotation;
};
