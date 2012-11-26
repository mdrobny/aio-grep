#ifndef FILEINFO_H
#define FILEINFO_H
#include <iostream>
#include <aio.h>
using namespace std;

class FileInfo
{
    size_t next;
    string fileName;
    long currentLine;
    int bufLength;
    aiocb * aioControl;
    string bufRest;
public:
    void setBufLength(int bL) { bufLength = bL;}
    int getBufLength() { return bufLength;}
    void setBufRest(string s) { bufRest = s;}
    string getBufRest() { return bufRest;}
    void setNext(int i) { next = i;}
    int getNext() {return next;}
    void plusLine() { ++currentLine;}
    long getCurrentLine() {return currentLine;}
    string & getName() {return fileName; }
    FileInfo(string name, aiocb * aioC);
    aiocb * getControl() { return aioControl; }
};

#endif // FILEINFO_H
