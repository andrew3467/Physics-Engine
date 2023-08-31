#include <iostream>
#include "Application.h"


int main() {
    try{
        Application app("Physics Engine");
        app.Run();
    }catch(std::exception &e){
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
