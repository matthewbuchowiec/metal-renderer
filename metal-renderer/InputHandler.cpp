//
//  InputHandler.cpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#include "InputHandler.hpp"
#include <iostream>

InputHandler::InputHandler()
    : wKeyDown(false), aKeyDown(false), sKeyDown(false), dKeyDown(false), mouseX(0), mouseY(0), prevMouseX(0), prevMouseY(0) {}

InputHandler::~InputHandler() {}

bool InputHandler::processInput(Camera& camera) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return true;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        return true;
                    case SDLK_w:
                        wKeyDown = true;
                        break;
                    case SDLK_a:
                        aKeyDown = true;
                        break;
                    case SDLK_s:
                        sKeyDown = true;
                        break;
                    case SDLK_d:
                        dKeyDown = true;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        wKeyDown = false;
                        break;
                    case SDLK_a:
                        aKeyDown = false;
                        break;
                    case SDLK_s:
                        sKeyDown = false;
                        break;
                    case SDLK_d:
                        dKeyDown = false;
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                float xrel = static_cast<float>(event.motion.xrel);
                float yrel = static_cast<float>(event.motion.yrel);
                camera.rotate(xrel, -yrel);
                break;
        }
    }

    if (wKeyDown) {
        camera.moveForward(0.1f);
    }
    if (sKeyDown) {
        camera.moveForward(-0.1f);
    }
    if (aKeyDown) {
        camera.moveRight(-0.1f);
    }
    if (dKeyDown) {
        camera.moveRight(0.1f);
    }


    return false;
}

