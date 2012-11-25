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

class AsynchronousFileReader : public FileReader
{
    list<FileInfo> fileList;
    int bufsize = 100;
    FileInfo * currentFile = NULL;

    string openBuf(FileInfo fInfo);
    string getLineFromBuf();
public:
    AsynchronousFileReader(int argc, char** argv, RegexFinder *&rf);
    void changeBufsize(int s){ bufsize = s;}
    ReadResult readLine(ResultLine& line);

};

#endif // ASYNCHRONOUSFILEREADER_H
