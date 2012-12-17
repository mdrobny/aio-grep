#include "output.h"
#include <ios>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define COLOR_AMOUNT 5

/*
 * Initializes colorList
 */
Output::Output(char methodChar, char *flagsChar) {
    flagLineNumbers=flagsChar[0];
    flagFileNames=flagsChar[1];
    switch(methodChar){
        case 's':
            frMethod="synchronous"; break;
        case 'a':
            frMethod="asynchronous"; break;
        case 'm':
            frMethod="mmap"; break;
    }
    currentFileName=std::string("");
    totalOcc=0;
}

/*
 * prints results
 * typedef int_pair_t from ResultLine.h
 */
void Output::printResult(ResultLine& l){
    std::ios_base::sync_with_stdio(false);
    int_pair_t o;       //pair of occurence
    int_pair_t* occ;    //array of pairs
    size_t nr;          //getNumberOfOccurences() value

    //file names
    if(flagFileNames) {// && currentFileName.compare(l.getFilename())!=0){
        std::cout << BLUE << l.getFilename() <<": "<<RESET;// << std::endl;
        //currentFileName=l.getFilename();
    }
    nr=l.getNumberOfOccurences();
    totalOcc+=nr;

    //if more than 1 occurence
    if(nr>1){
        occ=new int_pair_t[nr];
        for(int i=0; i < nr; i++){
            occ[i]=l.getOccurence(i);
        }
        if(flagLineNumbers)
            std::cout<< l.getLineNum() <<": ";
        std::cout<< RESET<< l.getLine().substr(0,occ[0].first) << RED;
        for(int i=0; i < nr; i++){
            std::cout<< l.getLine().substr(occ[i].first,occ[i].second - occ[i].first) << RESET;
            if((i+1) < nr)
                std::cout<< l.getLine().substr(occ[i].second,occ[i+1].first - occ[i].second) << RED;
            else
                std::cout<< l.getLine().substr(occ[i].second);
        }

        delete occ;
    } else {
    //if only 1 occurence
        o = l.getOccurence(0);
        if(flagLineNumbers)
            std::cout<< l.getLineNum() <<": ";
        std::cout<< RESET
                 << l.getLine().substr(0,o.first) << RED
                 << l.getLine().substr(o.first,o.second-o.first) << RESET
                 << l.getLine().substr(o.second) <<"\n";

    }
    //std::cout<<"\n"; //tests
}

void Output::printSummary(Timer& time){
    std::cout<<"SUMMARY:\n \t Total occurence amount: "<< RED << totalOcc << RESET <<"\n"
            <<"\t Method used: "<< RED << frMethod<< RESET << "\n"
           <<"\t Process time: "<< time.getTime() <<std::endl;
}
