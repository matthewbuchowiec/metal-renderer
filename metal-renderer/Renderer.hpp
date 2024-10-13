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

    // Render a given scene
    void render(const Scene& scene);

private:
    // Metal and rendering-related objects
    MTL::Device* device;
    MTL::CommandQueue* commandQueue;
    CA::MetalLayer* metalLayer;
    
    // Resource managers
    ResourceManager resourceManager;
    ShaderManager shaderManager;

    // Pipeline and depth stencil states
    MTL::RenderPipelineState* pipelineState;
    MTL::DepthStencilState* depthStencilState;
    MTL::Texture* depthTexture;

    // Create the render pipeline and depth stencil states
    MTL::VertexDescriptor* createVertexDescriptor();
    void createPipelineState();
    void setupDepthStencilState();
};

