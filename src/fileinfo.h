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
    bool isEof() { return eof;}
    void setBufLength(int bL) { bufLength = bL;}
    int getBufLength() { return bufLength;}
    void setBufRest(char * s, int n) { bufRest.replace(0,n,s); isBufRest = true;}
    string getBufRest() { isBufRest = false; return bufRest;}
    bool isRest() { return isBufRest;}
    void setNext(char* p) { nextP = p;}
    char * getNext() {return nextP;}
    void setEnd(char* p) { endP = p;}
    char * getEnd() {return endP;}
    void plusLine() { ++currentLine;}
    long getCurrentLine() {return currentLine;}
    char * getName() { return fileName; }
    void setName(char * fP) { fileName = fP; }
    FileInfo(char * name, aiocb * aioC);
    ~FileInfo();
    aiocb * getControl() { return aioControl; }
};

#endif // FILEINFO_H
