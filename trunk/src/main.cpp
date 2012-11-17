#include <iostream>
#include "synchronousfilereader.h"
#include "ResultLine.h"

int main(int argc, char** argv)
{
    SynchronousFileReader sfr(argc, argv);
    for(int i=0; i < 100; ++i)
    {
        ResultLine l = sfr.readLine();
        std::cout << "In file: " << l.getFilename() << "\n";
        std::cout << l.getLineNum() << ":\t" << l.getLine() << "\n" << std::endl;
    }
}

