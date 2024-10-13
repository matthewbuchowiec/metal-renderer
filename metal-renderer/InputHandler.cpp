//
//  InputHandler.cpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#include "InputHandler.hpp"

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

bool InputHandler::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return true;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        return true;
                }
                break;
        }
    }
    return false;
}
