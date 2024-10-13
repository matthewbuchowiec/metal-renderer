//
//  Mesh.hpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#pragma once

#include <vector>
#include <simd/simd.h>

struct Vertex {
    simd::float3 position;
    simd::float4 color;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices);

    const std::vector<Vertex>& getVertices() const { return vertices; }
    const std::vector<uint16_t>& getIndices() const { return indices; }

private:
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
};
