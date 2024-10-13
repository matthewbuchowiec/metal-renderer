//
//  ResourceManager.hpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#pragma once

#include <Metal/Metal.hpp>
#include "Mesh.hpp"

class ResourceManager {
public:
    ResourceManager(MTL::Device* device);
    ~ResourceManager();

    MTL::Buffer* createVertexBuffer(const std::vector<Vertex>& vertices);
    MTL::Buffer* createIndexBuffer(const std::vector<uint16_t>& indices);

private:
    MTL::Device* device;
};
