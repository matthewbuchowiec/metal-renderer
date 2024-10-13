//
//  InputHandler.hpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#pragma once

#include <SDL2/SDL.h>
#include "Camera.hpp"

class InputHandler {
public:
    InputHandler();
    ~InputHandler();

    bool processInput(Camera& camera);

private:
    bool wKeyDown, aKeyDown, sKeyDown, dKeyDown;
    int mouseX, mouseY;
    int prevMouseX, prevMouseY;
};

