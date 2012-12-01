#include <iostream>
#include "synchronousfilereader.h"
#include "asynchronousfilereader.h"
#include "resultline.h"
#include "regexfinder.h"
#include "dummyregexfinder.h"
#include "boostregexfinder.h"

/// Regex testing defines, uncomment the one that is needed
#define TEST_BOOSTREGEX
//#define TEST_DUMMYREGEX

/// File reader testing defines, uncomment the one that is needed
#define TEST_AIO
//#define TEST_SYNC

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <regex> <files>" << std::endl;
        return 1;
    }

#ifdef TEST_BOOSTREGEX
    RegexFinder* rf = new BoostRegexFinder(argv[1]);
#endif

#ifdef TEST_DUMMYREGEX
    RegexFinder* rf = new DummyRegexFinder(argv[1]);
#endif

#ifdef TEST_SYNC
    SynchronousFileReader fr(argc, argv, rf);
#endif

#ifdef TEST_AIO
    AsynchronousFileReader fr(argc, argv, rf);
#endif
    ResultLine l;
    FileReader::ReadResult r;
    while((r = fr.readLine(l)) != FileReader::FR_NO_MORE)
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

