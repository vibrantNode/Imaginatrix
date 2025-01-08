#include "Engine.h"


#include <iostream>




// Prevent accidentally selecting integrated GPU
extern "C" {
    __declspec(dllexport) unsigned __int32 AmdPowerXpressRequestHighPerformance = 0x1;
    __declspec(dllexport) unsigned __int32 NvOptimusEnablement = 0x1;
}

int main() {
    std::cout << "Imaginatrix starting\n" << std::endl;

    Engine::run();
}





