//
//  Scene.cpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#include "Scene.hpp"
#include <cmath>

Scene::Scene() : cube(createCubeMesh()), camera(), cubeModelMatrix(matrix_identity_float4x4), cubeRotationAngle(0.0f) {}

Scene::~Scene() {}

void Scene::initialize() {
    
}

void Scene::update() {
    updateNormalMatrix();
}

void Scene::updateNormalMatrix() {
    simd::float4x4 inverseModelMatrix = simd::inverse(cubeModelMatrix);
    normalMatrix = simd::transpose(inverseModelMatrix);
}

Mesh Scene::createCubeMesh() {
    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, -0.5f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {-1.0f, -1.0f, -1.0f}},
        {{0.5f, -0.5f, -0.5f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, -1.0f, -1.0f}},
        {{0.5f, 0.5f, -0.5f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, -1.0f}},
        {{-0.5f, 0.5f, -0.5f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}, {-1.0f, 1.0f, -1.0f}},
        {{-0.5f, -0.5f, 0.5f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}, {1.0f, -1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f, 1.0f}, {0.5f, 0.5f, 0.5f, 1.0f}, {-1.0f, 1.0f, 1.0f}}
    };

    // The indices remain the same
    std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0,
        1, 5, 6, 6, 2, 1,
        5, 4, 7, 7, 6, 5,
        4, 0, 3, 3, 7, 4,
        3, 2, 6, 6, 7, 3,
        4, 5, 1, 1, 0, 4
    };

    return Mesh(vertices, indices);
}
