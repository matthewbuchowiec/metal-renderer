//
//  ResourceManager.hpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#pragma once

#include <Metal/Metal.hpp>
#include <unordered_map>
#include "Mesh.hpp"

class ResourceManager {
public:
    ResourceManager(MTL::Device* device);
    ~ResourceManager();

    MTL::Buffer* getVertexBuffer(const Mesh& mesh);
    MTL::Buffer* getIndexBuffer(const Mesh& mesh);

private:
    MTL::Device* device;

    std::unordered_map<const Mesh*, MTL::Buffer*> vertexBuffers;
    std::unordered_map<const Mesh*, MTL::Buffer*> indexBuffers;

    MTL::Buffer* createVertexBuffer(const std::vector<Vertex>& vertices);
    MTL::Buffer* createIndexBuffer(const std::vector<uint16_t>& indices);
};

