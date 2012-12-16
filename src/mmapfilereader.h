#ifndef MMAPFILEREADER_H
#define MMAPFILEREADER_H

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "filereader.h"
#include "resultline.h"
#include <string.h>

class MmapFileReader : public FileReader
{
public:
    std::string currentFileName;

    MmapFileReader(int argc, char** argv, RegexFinder*& rf);
    ReadResult readLine(ResultLine& line);

private:
    std::vector<std::string > fileList;
    int sizeIterator;
    int lineEnd;
    int currentLineNr;
    bool eof;

    int currentFile;
    size_t size;
    const char *mapped;

};

#endif // MMAPFILEREADER_H
