#include "output.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define COLOR_AMOUNT 5

/*
 * Initializes colorList
 */
Output::Output(char printTypeFlag,FileReader* fileReader, std::string& fileReaderMethod) {
    printType=printTypeFlag;
    fr=fileReader;
    frMethod=fileReaderMethod;
    //colorList=new std::string[COLOR_AMOUNT];
    /*colorList[0]=RESET; colorList[1]=RED; colorList[2]=GREEN; colorList[3]=YELLOW;
    colorList[4]=BLUE;*/
    //colorIt=0;
}

Output::~Output(){
    //delete colorList;
}

/*
 * prints results
 * typedef int_pair_t from ResultLine.h
 */
void Output::printResults(){

    int_pair_t o;       //pair of occurence
    int_pair_t* occ;    //array of pairs
    size_t nr;          //getNumberOfOccurences() value
    int totalOcc=0;     //total occurences amount

    ResultLine l;
    FileReader::ReadResult r;
    while((r = fr->readLine(l)) != FileReader::FR_NO_MORE) {
        if(r == FileReader::FR_GOOD) {
            std::cout << "In file: " << l.getFilename() << "\n";
            nr=l.getNumberOfOccurences();
            totalOcc+=nr;

            //if more than 1 occurence
            if(nr>1){
                occ=new int_pair_t[nr];
                for(int i=0; i < nr; i++) {
                    occ[i]=l.getOccurence(i);
                    //std::cout<<occ[i].first<<":"<<occ[i].second<<std::endl;
                }

                std::cout<< l.getLineNum() <<":\t"<< RESET
                         << l.getLine().substr(0,occ[0].first) << RED;
                for(int i=0; i < nr; i++){
                    std::cout<< l.getLine().substr(occ[i].first,occ[i].second - occ[i].first) << RESET;
                    if((i+1) < nr)
                        std::cout<< l.getLine().substr(occ[i].second,occ[i+1].first - occ[i].second) << RED;
                    else
                        std::cout<< l.getLine().substr(occ[i].second);
                }
                std::cout<<"\n"<<std::endl;

                delete occ;
            } else {
            //if only 1 occurence
                o = l.getOccurence(0);
                std::cout<< l.getLineNum() <<":\t"<< RESET
                         << l.getLine().substr(0,o.first) << RED
                         << l.getLine().substr(o.first,o.second-o.first) << RESET
                         << l.getLine().substr(o.second) <<"\n"<<std::endl;
            }
            std::cout << "\n" << std::endl;
        }
        else if (r == FileReader::FR_OPEN_FAILED)
        {
            std::cout << "ERROR: File open failed in file: " << l.getFilename() << std::endl;
        }
    }

    std::cout<<"SUMMARY:\n \t Total occurence amount: "<< RED << totalOcc << RESET <<"\n"
            <<"\t Method used: "<< RED << frMethod<< RESET << "\n"
            <<"\t Process time: "<<std::endl;

}

/*
 * changes color
 * NOT IN USE (YET)
 */
/*std::string Output::chooseColor(){
    if(colorIt >= COLOR_AMOUNT) colorIt=0;
    return colorList[colorIt++];
}*/
