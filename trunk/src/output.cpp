#include "output.h"
#include <ios>
#include <cstring>
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
    std::ios_base::sync_with_stdio(false);
    offset_increment = strlen(RESET) + strlen(RED);
    colorLines=false;
}

/*
 * prints results
 * typedef int_pair_t from ResultLine.h
 */
void Output::printResult(ResultLine& l){

    int nr=l.getNumberOfOccurences();
    totalOcc+=nr;
	std::string tmp = l.getLine();
    //if more than 1 occurence
    if(colorLines) {
		offset = 0;
		for(int i=0; i<nr; ++i)
		{
			int_pair_t occ = l.getOccurence(i);
			if(flagLineNumbers)
				std::cout<< l.getLineNum() <<": ";
			tmp.insert(occ.second+offset, RESET);
			tmp.insert(occ.first+offset, RED);
			offset += offset_increment;
		}
	} 
    std::cout << tmp << "\n";
    //std::cout<<"\n"; //tests
}

void Output::setColorLines(bool c)
{
	colorLines = c;
}
void Output::printSummary(Timer& time){
    std::cout<<"SUMMARY:\n \t Total occurence amount: "<< RED << totalOcc << RESET <<"\n"
            <<"\t Method used: "<< RED << frMethod<< RESET << "\n"
           <<"\t Process time: "<< time.getTime() <<std::endl;
}
