//
//  ResourceManager.cpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#include "ResourceManager.hpp"

ResourceManager::ResourceManager(MTL::Device* device) : device(device) {}

ResourceManager::~ResourceManager() {}

MTL::Buffer* ResourceManager::createVertexBuffer(const std::vector<Vertex>& vertices) {
    return device->newBuffer(vertices.data(), vertices.size() * sizeof(Vertex), MTL::ResourceOptionCPUCacheModeDefault);
}

MTL::Buffer* ResourceManager::createIndexBuffer(const std::vector<uint16_t>& indices) {
    return device->newBuffer(indices.data(), indices.size() * sizeof(uint16_t), MTL::ResourceOptionCPUCacheModeDefault);
}
