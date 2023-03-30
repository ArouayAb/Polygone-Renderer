#include <iostream>
#include "Engine.hpp"

int main()
{
    try {
        dvk::Engine engine;
        engine.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

//    dvk::Core application;
//    try {
//    application.run();
//    } catch (std::exception& e) {
//        std::cerr << e.what() << std::endl;
//        return EXIT_FAILURE;
//    }
}