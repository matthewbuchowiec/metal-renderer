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
    const Camera& getCamera() const { return camera; }
    const simd::float4x4& getCubeModelMatrix() const { return cubeModelMatrix; }

private:
    Mesh cube;
    Camera camera;
    simd::float4x4 cubeModelMatrix;
    float cubeRotationAngle;
    
    static Mesh createCubeMesh();
};
