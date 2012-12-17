#include "flags.h"

/*
 * parsing flags
 * Fabric for RegexFinder object
 *            FileReader object
 */
Flags::Flags(int argc, char** argv){

    int opt;
    methodChar=0;
    flagsChar=new char[2]; for(int i=0;i<2;i++) flagsChar[i]=0;
    bool flagGiven=false;
    char flagCaseInsensitivity=0;

    /*flag passed
     *'a' xor 's' xor 'm'
     *'i' - case insensitive
     *'n' - show line numbers
     *'h' - file names
     */
    opterr=0; //no stderr
    while((opt=getopt(argc,argv,"samih")) !=-1){
        if(opt=='s' && methodChar==0){
            methodChar='s';
        } else if(opt=='a' && methodChar==0){
            methodChar='a';
        } else if(opt=='m' && methodChar==0){
            methodChar='m';
        }
        switch(opt){
        case 'i':
            flagCaseInsensitivity='i';
            break;
        case 'n':
            flagsChar[0]='n';
            break;
        case 'h':
            flagsChar[1]='h';
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
        case 'm':
            fr= new MmapFileReader(argc,argv,rf);
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
