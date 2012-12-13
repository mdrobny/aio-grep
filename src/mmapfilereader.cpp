#include "mmapfilereader.h"

MmapFileReader::MmapFileReader(int argc, char** argv, RegexFinder*& rf) :
    FileReader(argc,argv,rf) {

    for(int i=2;i<argc;++i)
        fileList.push_back(argv[i]);

    sizeIterator=0;
    lineEnd=0;
    currentLineNr=0;
    eof=true;

    currentFile=-3;
    size=0;
    mapped=0;


}

FileReader::ReadResult MmapFileReader::readLine(ResultLine& line){
    line.clear();

    if(eof==true){

        if(currentFile>0) close(currentFile);

        if(fileList.size() == 0)
            return FR_NO_MORE;
        currentFileName = fileList.back();
        fileList.pop_back();

        line.setFilename(currentFileName);

        currentFile=open(currentFileName.c_str(),O_RDONLY);
        if(currentFile<0) return FR_OPEN_FAILED;

        eof=false;

        //start of mapping process
        struct stat s;
        int status;

        status=fstat(currentFile,&s);
        if(status<0) return FR_OPEN_FAILED;
        size=s.st_size;

        mapped=(const char*) mmap(0,size,PROT_READ,MAP_PRIVATE,currentFile,0);
        if(mapped==MAP_FAILED) return FR_OPEN_FAILED;

    } else {

        while(sizeIterator<size){
            if(mapped[sizeIterator]=='\n'){
                std::string tmp(mapped+lineEnd,sizeIterator-lineEnd);

                sizeIterator++;
                currentLineNr++;
                lineEnd=sizeIterator;

                line.setLine(tmp);
                if(regexFinder->checkLine(line) == true){
                    line.setFilename(currentFileName);
                    line.setLineNum(currentLineNr);
                    return FR_GOOD;
                }

            } else {
                sizeIterator++;
            }
        }
        //end of file, reset counters
        if(sizeIterator>=size) {
            eof=true;
            sizeIterator=0;
            currentLineNr=0;
            lineEnd=0;
        }
    }
    return FR_BAD;
}
