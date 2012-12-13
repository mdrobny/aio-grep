#include "flags.h"

/*
 * parsing flags
 * Fabric for RegexFinder object
 *            FileReader object
 */
Flags::Flags(int argc, char** argv){

    int opt;
    methodChar=0;
    flagsChar=new char[1]; flagsChar[0]=0;
    bool flagGiven=false;
    char flagCaseInsensitivity=0;

    /*flag passed
     *'a' xor 's'
     *'i' - case insensitive
     *'h' - show line numbers
     */
    opterr=0; //no stderr
    while((opt=getopt(argc,argv,"saih")) !=-1){
        if(opt=='s' && methodChar==0){
            methodChar='s';
        } else if(opt=='a' && methodChar==0){
            methodChar='a';
        }
        switch(opt){
        case 'i':
            flagCaseInsensitivity='i';
            break;
        case 'h':
            flagsChar[0]='h';
            break;
        case '?':
            std::cout<<"There's no flag '-"<<(char)optopt<<"'"<<std::endl;
            break;
        default:
              ;
        }
        if(!flagGiven) flagGiven=true;
    }
    if(flagGiven) correctArgs(argc,argv,optind);

    //creating RefexFinder
    rf=initRegexFinder(argv[1]);

    //creating proper FileReader
    switch(methodChar){
        case 's':
            fr= new SynchronousFileReader(argc, argv, rf);
            break;
        case 'a':
            fr= new AsynchronousFileReader(argc, argv, rf);
            break;
        default:
        //no flags so SYNC
            fr= new SynchronousFileReader(argc, argv, rf);
    }
}

FileReader* Flags::getFileReader() {
    return fr;
}

/*
 * switch argv[i] value with next argv value (argv[i+1])
 * to keep proper regex and files order
 * optind is the index in argv of the first argv-element that is not an option.
 */
void Flags::correctArgs(int& argc, char** argv,int optind){
    int i;
    for(i=1;i < argc;++i) argv[i]=argv[i+optind-1];
    argc=argc-optind+1;
}


/*
 * initialize choosen RegexFinder
 */
RegexFinder* Flags::initRegexFinder(char* rgx){
    //return new BoostRegexFinder(rgx);
    return new DummyRegexFinder(rgx);
    //return new RE2RegexFinder(rgx);
}

Flags::~Flags(){
    delete fr;
    delete rf;
    delete flagsChar;
}
