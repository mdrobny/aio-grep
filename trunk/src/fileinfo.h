#ifndef FILEINFO_H
#define FILEINFO_H
#include <iostream>
#include <aio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
using namespace std;

class FileInfo
{
    char * fileName;
    long currentLine;
    int bufLength;
    aiocb * aioControl;
    std::string bufRest;
    bool eof;
    bool isBufRest;
    char * nextP;
    char * endP;

public:
    void setEof() { eof = true;  }
    void unsetEof() { eof = false;  }
    bool isEof() { return eof;}
    void setBufLength(int bL) { bufLength = bL;}
    int getBufLength() { return bufLength;}
    void setBufRest(char * s, int n) { bufRest.replace(0,n,s); isBufRest = true;}
    string getBufRest(){isBufRest = false; return bufRest;}
    void unsetRest() { isBufRest = false;}
    bool isRest() { return isBufRest;}
    void setNext(char* p) { nextP = p;}
    char * getNext() {return nextP;}
    void setEnd(char* p) { endP = p;}
    char * getEnd() {return endP;}
    void plusLine() { ++currentLine;}
    void zeroLine() { currentLine = 0;}
    long getCurrentLine() {return currentLine;}
    char * getName() { return fileName; }
    void setName(char * fP) { fileName = fP; }
    FileInfo(char * name, aiocb * aioC);
    ~FileInfo();
    aiocb * getControl() { return aioControl; }
    void setControl(aiocb * p) { aioControl = p; }
};

#endif // FILEINFO_H
