

#include <iostream>
#include "synchronousfilereader.h"
#include "ResultLine.h"

int main(int argc, char** argv)
{
    SynchronousFileReader sfr(argc, argv);
    ResultLine l;
    FileReader::ReadResult r;
    while((r = sfr.readLine(l)) != FileReader::FR_NO_MORE)
    {
        if(r == FileReader::FR_GOOD) {
            std::cout << "In file: " << l.getFilename() << "\n";
            std::cout << l.getLineNum() << ":\t" << l.getLine() << "\n" << std::endl;
        }
    }
}

