//
//  ShaderManager.cpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#include "ShaderManager.hpp"
#include <iostream>

ShaderManager::ShaderManager(MTL::Device* device) : device(device) {
    NS::Error* error = nullptr;
    defaultLibrary = device->newDefaultLibrary();
    if (!defaultLibrary) {
        std::cerr << "Failed to create default library" << std::endl;
    }
}

ShaderManager::~ShaderManager() {
    defaultLibrary->release();
}

MTL::Function* ShaderManager::getVertexShader(const std::string& name) {
    return defaultLibrary->newFunction(NS::String::string(name.c_str(), NS::StringEncoding::UTF8StringEncoding));
}

MTL::Function* ShaderManager::getFragmentShader(const std::string& name) {
    return defaultLibrary->newFunction(NS::String::string(name.c_str(), NS::StringEncoding::UTF8StringEncoding));
}
