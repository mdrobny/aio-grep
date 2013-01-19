#ifndef ASYNCHRONOUSFILEREADER_H
#define ASYNCHRONOUSFILEREADER_H

#include <iostream>
#include <list>
#include "filereader.h"
#include "fileinfo.h"
#include "resultline.h"
#include <aio.h>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <stdlib.h>

typedef std::pair<int, int> int_pair_t;

class AsynchronousFileReader : public FileReader
{
    list<FileInfo> fileList;
    int bufsize;
    FileInfo * currentFile;
    int aiocbAmount;
    aiocb ** aioList;

    string openBuf(FileInfo & fInfo, int ret);
    string getLineFromBuf();
    int startNextRead(aiocb * aio);
public:
    AsynchronousFileReader(int argc, char** argv, RegexFinder *rf);
    ~AsynchronousFileReader();
    void changeBufsize(int s){ bufsize = s;}
    ReadResult readLine(ResultLine& line);

};

#endif // ASYNCHRONOUSFILEREADER_H