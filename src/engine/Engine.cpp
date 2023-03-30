//
// Created by Arouay on 29/03/2023.
//

#include "Engine.hpp"

namespace dvk {

    void Engine::init() {

    }

    Engine::Engine() {
        init();
    }

    void Engine::run() {
        this->window.startLoop([](){
            std::cout << "frame draw" << std::endl;
//            drawFrame();
        });
    }
}
