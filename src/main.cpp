

#include <iostream>
#include "synchronousfilereader.h"
#include "resultline.h"
#include "regexfinder.h"
#include "dummyregexfinder.h"
#include "cpp11regexfinder.h"

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <regex> <files>" << std::endl;
        return 1;
    }
    RegexFinder* rf = new Cpp11RegexFinder();
    SynchronousFileReader sfr(argc, argv, rf);
    ResultLine l;
    FileReader::ReadResult r;
    while((r = sfr.readLine(l)) != FileReader::FR_NO_MORE)
    {
        if(r == FileReader::FR_GOOD) {
            std::cout << "In file: " << l.getFilename() << "\n";
            std::cout << l.getLineNum() << ":\t" << l.getLine() << "\n" << std::endl;
            std::cout << l.getNumberOfOccurences() << " occurences between: \n";
            for(int i=0; i < l.getNumberOfOccurences(); i++) {
                int_pair_t o = l.getOccurence(i);
                std::cout << o.first << " " << o.second << "\n";
            }
            std::cout << "\n" << std::endl;
        }
        else if (r == FileReader::FR_OPEN_FAILED)
        {
            std::cout << "ERROR: File open failed in file: " << l.getFilename() << std::endl;
        }
    }
    delete rf;
    return 0;
}

