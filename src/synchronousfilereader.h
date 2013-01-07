#ifndef SYNCHRONOUSFILEREADER_H
#define SYNCHRONOUSFILEREADER_H

#include <iostream>
#include <fstream>

#include "filereader.h"
#include "resultline.h"
#include <string.h>

///
/// @class SynchronousFileReader
/// @brief File reader that performs synchronous reading.
/// This file reader uses std::getline(...) function to read lines from files. Works on std::string objects.
///
class SynchronousFileReader : public FileReader
{
private:
    std::ifstream currentFile;
    int currentLine;
    std::string currentFilename;
    std::vector<std::string > fileList;
public:
    ///
    /// @brief @see{FileReader}
    ///
    SynchronousFileReader(int argc, char** argv, RegexFinder*& rf);

    ///
    /// @brief @see{FileReader}
    ///
    ReadResult readLine(ResultLine& line);
};

#endif // SYNCHRONOUSFILEREADER_H
