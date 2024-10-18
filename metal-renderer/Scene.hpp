//
//  Scene.hpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#pragma once

#include "Mesh.hpp"
#include "Camera.hpp"

class Scene {
public:
    Scene();
    ~Scene();

    void initialize();
    void update();

    const Mesh& getCube() const { return cube; }
    Camera& getCamera() { return camera; }
    const simd::float4x4& getCubeModelMatrix() const { return cubeModelMatrix; }
    const simd::float4x4& getNormalMatrix() const { return normalMatrix; }

private:
    Mesh cube;
    Camera camera;
    simd::float4x4 cubeModelMatrix;
    float cubeRotationAngle;
    simd::float4x4 normalMatrix;

    void updateNormalMatrix();
    
    static Mesh createCubeMesh();
};
