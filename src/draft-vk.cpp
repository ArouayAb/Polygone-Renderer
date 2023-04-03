#include <iostream>
#include "Engine.hpp"
#include "_Core.hpp"

int main()
{
    try {
        dvk::Engine engine;
        engine.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}