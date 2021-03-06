#include "agrep.h"

Agrep::Agrep(int argc, char **argv){

    Timer time=Timer();

    Flags flagManager=Flags(argc,argv);
    FileReader* fr=flagManager.getFileReader();  //fileReader

    Output output=Output(flagManager.methodChar,flagManager.flagsChar);
	output.setColorLines(flagManager.getColorLines());
    ResultLine l;
    FileReader::ReadResult r;
    while((r = fr->readLine(l)) != FileReader::FR_NO_MORE) {
        if(r == FileReader::FR_GOOD) {
            output.printResult(l);


        } else if (r == FileReader::FR_OPEN_FAILED){
            std::cout << "ERROR: File open failed in file: " << l.getFilename() << std::endl;
        }


    }
    if(flagManager.getPrintSummaryFlag())
		output.printSummary(time);

}


