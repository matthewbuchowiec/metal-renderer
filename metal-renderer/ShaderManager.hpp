//
//  ShaderManager.hpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#pragma once

#include <Metal/Metal.hpp>
#include <string>

class ShaderManager {
public:
    ShaderManager(MTL::Device* device);
    ~ShaderManager();

    MTL::Function* getVertexShader(const std::string& name);
    MTL::Function* getFragmentShader(const std::string& name);

private:
    MTL::Device* device;
    MTL::Library* defaultLibrary;
};
