#ifndef MMAPFILEREADER_H
#define MMAPFILEREADER_H

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "filereader.h"
#include "resultline.h"
#include <string.h>


///
/// @brief File reader that performs mmap reading.
/// @author Michał Drobniak
/// uses mmap() function from unistd.h to create a virtual file's map and works on it
///
/**
 * sizeIterator - iterates to reach file's size
 * lineEnd - position of last caught '\n' char
 * eof - if sizeIterator reached size it's takes a true value
 * currentFile - file descriptor
 * size - file's size get from stats.h
 * mapped - mapped file
 **/
class MmapFileReader : public FileReader
{
public:
    std::string currentFileName;

    MmapFileReader(int argc, char** argv, RegexFinder*& rf);
    ///
    /// @brief loads file statistics and create file's map
    /// iterates char by char in virtual map
    /// uses std::string
    ///
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
