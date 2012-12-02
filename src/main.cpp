#include <iostream>
#include "synchronousfilereader.h"
#include "asynchronousfilereader.h"
#include "resultline.h"
#include "output.h"
#include "regexfinder.h"
#include "dummyregexfinder.h"
#include "boostregexfinder.h"

#include <unistd.h>     //getoption function


/// Regex testing defines, uncomment the one that is needed
//#define TEST_BOOSTREGEX
#define TEST_DUMMYREGEX

/*
 * switch argv[i] value with next argv value (argv[i+1])
 * to keep proper regex and files order
 */
void correctArgs(int& argc, char** argv){
    int i;
    for(i=1;i < argc;++i) argv[i]=argv[i+1];
    argc--;
}

/*
 * initialize choosen RegexFinder
 */
RegexFinder* initRegexFinder(std::string rgx){
    #ifdef TEST_BOOSTREGEX
        return new BoostRegexFinder(rgx);
    #endif

    #ifdef TEST_DUMMYREGEX
        return new DummyRegexFinder(rgx);
    #endif
}

int main(int argc, char** argv)
{
    if(argc < 3){
        std::cout << "Usage: " << argv[0] << "[-options] <regex> <files>" << std::endl;
        return 1;
    }


RegexFinder* rf; //RegexFinder object
FileReader* fr;  //FileReader object

/*** FLAGS ****/
int opt;
std::string frMethod="synchronous"; //passed to Output object


//if 'a' xor 's' flag passed
if((opt=getopt(argc,argv,"sa")) !=-1){
    rf=initRegexFinder(argv[2]);

    switch(opt){
    case 's':
        //std::cout<<"SYNC\n"<<std::endl;
        correctArgs(argc,argv);
        fr= new SynchronousFileReader(argc, argv, rf);
        break;
    case 'a':
        //std::cout<<"aSYNC\n"<<std::endl;
        correctArgs(argc,argv);
        fr= new AsynchronousFileReader(argc, argv, rf);
        frMethod="asynchronous";
        break;
    case '?':
        std::cout << argv[0] <<": Wrong flag. Possible flags: -a -s " << std::endl;
        return 1;
        break;
    default:
          ;
    }
//no flags passed so sync
} else {
    //std::cout<<"brak flag: SYNC\n"<<std::endl;
    rf=initRegexFinder(argv[1]);
    fr=new SynchronousFileReader(argc, argv, rf);
    //fr= new AsynchronousFileReader(argc, argv, rf);

}
/**************/

//DEBUG
//std::cout<<"argc: "<<argc<<std::endl;
//for(int i = 0; i < argc; ++i) { std::cout<<"argv["<<i<<"]: "<<argv[i]<<std::endl;}

    Output output=Output('n',fr,frMethod);
    output.printResults();

    delete fr;
    delete rf;
    return 0;
}
