#include <filesystem>
#include "Core.hpp"
#include <iostream>
#include "Engine.hpp"

template<typename Lambda>
std::string cb_test(Lambda&& cb) {
    return cb();
}

int main()
{

    dvk::Engine engine;
    engine.run();

    std::cout << cb_test([]() -> std::string {
        return R"(
            #version 420 core

            void main(void)
            {
                gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
            }
        )";
    });
//    dvk::Core application;
//    try {
//    application.run();
//    } catch (std::exception& e) {
//        std::cerr << e.what() << std::endl;
//        return EXIT_FAILURE;
//    }
}