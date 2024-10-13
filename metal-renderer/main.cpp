//
//  main.cpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/12/24.
//

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_metal.h>
#include <iostream>
#include "Renderer.hpp"
#include "Scene.hpp"
#include "InputHandler.hpp"

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 660;

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("metal-renderer",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_METAL);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_MetalView metalView = SDL_Metal_CreateView(window);
    CA::MetalLayer* metalLayer = (CA::MetalLayer*)SDL_Metal_GetLayer(metalView);

    Renderer renderer(metalLayer);
    Scene scene;
    InputHandler inputHandler;

    scene.initialize();

    bool quit = false;
    while (!quit) {
        quit = inputHandler.processInput();
        scene.update();
        renderer.render(scene);
    }

    SDL_Metal_DestroyView(metalView);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
