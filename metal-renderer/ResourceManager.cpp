//
//  ResourceManager.cpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#include "ResourceManager.hpp"
#include <iostream>

ResourceManager::ResourceManager(MTL::Device* device) : device(device) {}

ResourceManager::~ResourceManager() {
    // Release all cached buffers
    for (auto& pair : vertexBuffers) {
        pair.second->release();
    }
    for (auto& pair : indexBuffers) {
        pair.second->release();
    }
}

MTL::Buffer* ResourceManager::getVertexBuffer(const Mesh& mesh) {
    // Check if vertex buffer already exists for this mesh
    auto it = vertexBuffers.find(&mesh);
    if (it != vertexBuffers.end()) {
        return it->second;
    }
    // Otherwise, create a new buffer and store it
    MTL::Buffer* buffer = createVertexBuffer(mesh.getVertices());
    vertexBuffers[&mesh] = buffer;
    return buffer;
}

MTL::Buffer* ResourceManager::getIndexBuffer(const Mesh& mesh) {
    // Check if index buffer already exists for this mesh
    auto it = indexBuffers.find(&mesh);
    if (it != indexBuffers.end()) {
        return it->second;
    }
    // Otherwise, create a new buffer and store it
    MTL::Buffer* buffer = createIndexBuffer(mesh.getIndices());
    indexBuffers[&mesh] = buffer;
    return buffer;
}

MTL::Buffer* ResourceManager::createVertexBuffer(const std::vector<Vertex>& vertices) {
    return device->newBuffer(vertices.data(), vertices.size() * sizeof(Vertex), MTL::ResourceOptionCPUCacheModeDefault);
}

MTL::Buffer* ResourceManager::createIndexBuffer(const std::vector<uint16_t>& indices) {
    return device->newBuffer(indices.data(), indices.size() * sizeof(uint16_t), MTL::ResourceOptionCPUCacheModeDefault);
}

