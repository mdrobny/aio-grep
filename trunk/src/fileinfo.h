#ifndef FILEINFO_H
#define FILEINFO_H
#include <iostream>
#include <aio.h>
using namespace std;

class FileInfo
{
    string fileName;
    long actLine;
    aiocb * aioControl;
public:
    FileInfo(string name, aiocb * aioC);
};

#endif // FILEINFO_H
