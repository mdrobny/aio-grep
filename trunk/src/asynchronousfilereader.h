///
///      @file  asynchronousfilereader.h
///     @brief  File reader that performs asynchronous reading.
/// This file reader uses aio.h library to read files. Reading files doesn't block program. Use mainly pointer to char.
///
///
///    @author  Marcin Piłat, reynev@gmail.com
///
/// This source code is released for free distribution under the terms of the
/// GNU General Public License as published by the Free Software Foundation.
///=====================================================================================
///

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
    string * out;
    std::pair<char *, char *> * ln;

    void openBuf(FileInfo & fInfo, int ret);
    void getLineFromBuf();
    int startNextRead(aiocb * aio);
    aiocb * prepareAioStruct(const char *, void *, aiocb *aio);
    void switchFile(list<FileInfo>::iterator fi);
public:
    ///
    /// @brief Constructor
    /// Allocate memory for buffers, create list of files, initiate reading files.
    ///
    AsynchronousFileReader(int argc, char** argv, RegexFinder *rf);
    ///
    /// @brief Destructor
    /// Free allocated memory.
    ///
    ~AsynchronousFileReader();
    ///
    /// @brief @see{FileReader}
    ///
    ReadResult readLine(ResultLine& line);

};

#endif // ASYNCHRONOUSFILEREADER_H
