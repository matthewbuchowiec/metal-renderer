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
    camera.setPosition({0, 0, 3});
}

void Scene::update() {
    cubeRotationAngle += 0.01f;
    simd::float4x4 rotationMatrix = simd::float4x4(
        simd::make_float4(cos(cubeRotationAngle), 0, sin(cubeRotationAngle), 0),
                                                   simd::make_float4(0, 1, 0, 0),
                                                   simd::make_float4(-sin(cubeRotationAngle), 0, cos(cubeRotationAngle), 0),
                                                   simd::make_float4(0, 0, 0, 1)
    );

    cubeModelMatrix = rotationMatrix;
}

Mesh Scene::createCubeMesh() {
    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f, 1.0f}}
    };

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
