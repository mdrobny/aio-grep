#include <iostream>
#include "synchronousfilereader.h"
#include "asynchronousfilereader.h"
#include "resultline.h"
#include "output.h"
#include "regexfinder.h"
#include "dummyregexfinder.h"
#include "boostregexfinder.h"

/// Regex testing defines, uncomment the one that is needed
//#define TEST_BOOSTREGEX
#define TEST_DUMMYREGEX

/// File reader testing defines, uncomment the one that is needed
//#define TEST_AIO
#define TEST_SYNC

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <regex> <files>" << std::endl;
        return 1;
    }

//TODO: flagi sync/async
    //ja się tym zajmę, Drobny
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

    Output output=Output('n',&fr);
    output.printResults();

    delete rf;
    return 0;
}
