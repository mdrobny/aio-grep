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
#include <utility>
#include <stdexcept>

typedef std::pair<int, int> int_pair_t;

class AsynchronousFileReader : public FileReader
{
    list<FileInfo> fileList;
    int bufsize;
    FileInfo * currentFile;
    int aiocbAmount;
    int lastWaitingNo;
    int _argc;
    char **_argv;
    aiocb ** aioList;
    char * generalBuf;
    string * tmp;
    std::pair<char *, char *> * ln;

    void openBuf(FileInfo & fInfo, int ret);
    void getLineFromBuf();
    int startNextRead(aiocb * aio);
    aiocb * prepareAioStruct(const char *, void *, aiocb *aio);
    void switchFile(list<FileInfo>::iterator fi);
public:
    AsynchronousFileReader(int argc, char** argv, RegexFinder *rf);
    ~AsynchronousFileReader();
    void changeBufsize(int s){ bufsize = s;}
    ReadResult readLine(ResultLine& line);

};

#endif // ASYNCHRONOUSFILEREADER_H
