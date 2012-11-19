

#include <iostream>
#include "synchronousfilereader.h"
#include "resultline.h"

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <regex> <files>" << std::endl;
        return 1;
    }
    SynchronousFileReader sfr(argc, argv);
    ResultLine l;
    FileReader::ReadResult r;
    while((r = sfr.readLine(l)) != FileReader::FR_NO_MORE)
    {
        if(r == FileReader::FR_GOOD) {
            std::cout << "In file: " << l.getFilename() << "\n";
            std::cout << l.getLineNum() << ":\t" << l.getLine() << "\n" << std::endl;
        }
        else if (r == FileReader::FR_OPEN_FAILED)
        {
            std::cout << "ERROR: File open failed in file: " << l.getFilename();
        }
    }

    return 0;
}

