#include "flags.h"

Flags::Flags(int argc, char** argv){

    int opt;
    frMethod="synchronous";

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
            //return 1;
            break;
        default:
              ;
        }
    //no flags passed so sync
    } else {
        //std::cout<<"brak flag: SYNC\n"<<std::endl;
        rf=initRegexFinder(argv[1]);
        fr=new SynchronousFileReader(argc, argv, rf);
    }

}

FileReader* Flags::getFileReader() {
    return fr;
}

/*
 * switch argv[i] value with next argv value (argv[i+1])
 * to keep proper regex and files order
 */
void Flags::correctArgs(int& argc, char** argv){
    int i;
    for(i=1;i < argc;++i) argv[i]=argv[i+1];
    argc--;
}


/*
 * initialize choosen RegexFinder
 */
RegexFinder* Flags::initRegexFinder(std::string rgx){
    //return new BoostRegexFinder(rgx);
    return new DummyRegexFinder(rgx);
    //return new RE2RegexFinder(rgx);
}

Flags::~Flags(){
    delete fr;
    delete rf;
}
