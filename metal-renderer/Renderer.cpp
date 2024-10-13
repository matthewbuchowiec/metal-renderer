//
//  Renderer.cpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#include "Renderer.hpp"
#include "Scene.hpp"
#include <iostream>

Renderer::Renderer(CA::MetalLayer* metalLayer)
    : metalLayer(metalLayer),
      device(MTL::CreateSystemDefaultDevice()),
      commandQueue(device->newCommandQueue()),
      resourceManager(device),
      shaderManager(device) {
    metalLayer->setDevice(device);
    metalLayer->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm);
    createPipelineState();
    setupDepthStencilState();
}

Renderer::~Renderer() {
    pipelineState->release();
    commandQueue->release();
    device->release();
}

MTL::VertexDescriptor* Renderer::createVertexDescriptor() {
    MTL::VertexDescriptor* vertexDescriptor = MTL::VertexDescriptor::alloc()->init();

    // Position
    vertexDescriptor->attributes()->object(0)->setFormat(MTL::VertexFormatFloat3);
    vertexDescriptor->attributes()->object(0)->setOffset(0);
    vertexDescriptor->attributes()->object(0)->setBufferIndex(0);

    // Color
    vertexDescriptor->attributes()->object(1)->setFormat(MTL::VertexFormatFloat4);
    vertexDescriptor->attributes()->object(1)->setOffset(sizeof(float) * 3);
    vertexDescriptor->attributes()->object(1)->setBufferIndex(0);

    vertexDescriptor->layouts()->object(0)->setStride(sizeof(Vertex));

    return vertexDescriptor;
}

void Renderer::createPipelineState() {
    MTL::Function* vertexFunction = shaderManager.getVertexShader("vertexShader");
    MTL::Function* fragmentFunction = shaderManager.getFragmentShader("fragmentShader");

    MTL::RenderPipelineDescriptor* pipelineStateDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    pipelineStateDescriptor->setVertexFunction(vertexFunction);
    pipelineStateDescriptor->setFragmentFunction(fragmentFunction);
    pipelineStateDescriptor->colorAttachments()->object(0)->setPixelFormat(metalLayer->pixelFormat());
    pipelineStateDescriptor->setDepthAttachmentPixelFormat(MTL::PixelFormat::PixelFormatDepth32Float);
    pipelineStateDescriptor->setVertexDescriptor(createVertexDescriptor());

    NS::Error* error = nullptr;
    pipelineState = device->newRenderPipelineState(pipelineStateDescriptor, &error);
    if (!pipelineState) {
        std::cerr << "Failed to create pipeline state: " << error->localizedDescription()->utf8String() << std::endl;
    }

    pipelineStateDescriptor->release();
    vertexFunction->release();
    fragmentFunction->release();
}

void Renderer::setupDepthStencilState() {
    MTL::DepthStencilDescriptor* depthStencilDesc = MTL::DepthStencilDescriptor::alloc()->init();
    depthStencilDesc->setDepthCompareFunction(MTL::CompareFunction::CompareFunctionLess);
    depthStencilDesc->setDepthWriteEnabled(true);

    depthStencilState = device->newDepthStencilState(depthStencilDesc);

    depthStencilDesc->release();
}

void Renderer::render(const Scene& scene) {
    CA::MetalDrawable* drawable = metalLayer->nextDrawable();
    
    MTL::TextureDescriptor* depthTextureDescriptor = MTL::TextureDescriptor::texture2DDescriptor(
            MTL::PixelFormat::PixelFormatDepth32Float,
            drawable->texture()->width(),
            drawable->texture()->height(),
            false);
    depthTextureDescriptor->setUsage(MTL::TextureUsageRenderTarget);
    depthTextureDescriptor->setStorageMode(MTL::StorageModePrivate);

    MTL::Texture* depthTexture = device->newTexture(depthTextureDescriptor);

    MTL::RenderPassDescriptor* renderPassDescriptor = MTL::RenderPassDescriptor::alloc()->init();
    renderPassDescriptor->colorAttachments()->object(0)->setTexture(drawable->texture());
    renderPassDescriptor->colorAttachments()->object(0)->setLoadAction(MTL::LoadAction::LoadActionClear);
    renderPassDescriptor->colorAttachments()->object(0)->setClearColor(MTL::ClearColor::Make(0.1, 0.1, 0.1, 1.0));

    renderPassDescriptor->setDepthAttachment(renderPassDescriptor->depthAttachment());
    renderPassDescriptor->depthAttachment()->setTexture(depthTexture);
    renderPassDescriptor->depthAttachment()->setLoadAction(MTL::LoadAction::LoadActionClear);
    renderPassDescriptor->depthAttachment()->setClearDepth(1.0);

    MTL::CommandBuffer* commandBuffer = commandQueue->commandBuffer();
    MTL::RenderCommandEncoder* renderEncoder = commandBuffer->renderCommandEncoder(renderPassDescriptor);

    renderEncoder->setRenderPipelineState(pipelineState);
    renderEncoder->setDepthStencilState(depthStencilState);

    // Set up vertex and index buffers
    const Mesh& cube = scene.getCube();
    MTL::Buffer* vertexBuffer = resourceManager.createVertexBuffer(cube.getVertices());
    MTL::Buffer* indexBuffer = resourceManager.createIndexBuffer(cube.getIndices());

    renderEncoder->setVertexBuffer(vertexBuffer, 0, 0);

    // Set up uniforms
    const Camera& camera = scene.getCamera();
    simd::float4x4 viewMatrix = camera.getViewMatrix();
    simd::float4x4 projectionMatrix = camera.getProjectionMatrix();
    simd::float4x4 modelMatrix = scene.getCubeModelMatrix();

    simd::float4x4 modelViewProjectionMatrix = matrix_multiply(projectionMatrix, matrix_multiply(viewMatrix, modelMatrix));

    renderEncoder->setVertexBytes(&modelViewProjectionMatrix, sizeof(modelViewProjectionMatrix), 1);
    renderEncoder->setFrontFacingWinding(MTL::Winding::WindingClockwise);
    renderEncoder->setCullMode(MTL::CullMode::CullModeBack);

    renderEncoder->drawIndexedPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle,
                                         cube.getIndices().size(),
                                         MTL::IndexType::IndexTypeUInt16,
                                         indexBuffer,
                                         0);

    renderEncoder->endEncoding();
    commandBuffer->presentDrawable(drawable);
    commandBuffer->commit();

    renderPassDescriptor->release();
    vertexBuffer->release();
    indexBuffer->release();
    depthStencilState->release();
}
