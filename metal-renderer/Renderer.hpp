//
//  Renderer.hpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#pragma once

#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include "ResourceManager.hpp"
#include "ShaderManager.hpp"

class Scene;

class Renderer {
public:
    Renderer(CA::MetalLayer* metalLayer);
    ~Renderer();

    void render(const Scene& scene);

private:
    MTL::Device* device;
    MTL::CommandQueue* commandQueue;
    CA::MetalLayer* metalLayer;
    ResourceManager resourceManager;
    ShaderManager shaderManager;

    MTL::RenderPipelineState* pipelineState;
    MTL::DepthStencilState* depthStencilState;

    MTL::VertexDescriptor* createVertexDescriptor();
    void createPipelineState();
    void setupDepthStencilState();
};
