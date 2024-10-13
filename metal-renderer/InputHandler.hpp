//
//  InputHandler.hpp
//  metal-renderer
//
//  Created by Matthew Buchowiec on 10/13/24.
//

#pragma once

#include <SDL2/SDL.h>

class InputHandler {
public:
    InputHandler();
    ~InputHandler();

    bool processInput();
};
