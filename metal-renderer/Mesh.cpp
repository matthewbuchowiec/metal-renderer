//
//  Mesh.cpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#include "Mesh.hpp"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices)
    : vertices(vertices), indices(indices) {}
