// CMakeProject1.cpp : Defines the entry point for the application.
//

#include "vk-draft.hpp"
#include "Core.hpp"

int main()
{
    Core application;
    try
    {
        application.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
