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
    // Constructor and destructor
    ResourceManager(MTL::Device* device);
    ~ResourceManager();

    // Retrieve vertex and index buffers for a given mesh (returns cached if exists)
    MTL::Buffer* getVertexBuffer(const Mesh& mesh);
    MTL::Buffer* getIndexBuffer(const Mesh& mesh);

private:
    MTL::Device* device;

    // Caches for storing buffers
    std::unordered_map<const Mesh*, MTL::Buffer*> vertexBuffers;
    std::unordered_map<const Mesh*, MTL::Buffer*> indexBuffers;

    // Internal methods to create buffers
    MTL::Buffer* createVertexBuffer(const std::vector<Vertex>& vertices);
    MTL::Buffer* createIndexBuffer(const std::vector<uint16_t>& indices);
};

