#include <iostream>
#include "agrep.h"


int main(int argc, char** argv)
{
    if(argc < 3){
        std::cout << "Usage: " << argv[0] << "[-options] <regex> <files>" << std::endl;
        return 1;
    }

    Agrep(argc,argv);

    return 0;
}
