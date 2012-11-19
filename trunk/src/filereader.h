#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <string>
#include <vector>
#include "resultline.h"

class FileReader
{

protected:
    //! list of all files to be searched
    std::vector<std::string > fileList;

    //! used temporarily as a substitude for real regex checking
    std::string regex;

public:
    //! puts filenames passed in commandline into fileList vector
    FileReader(int argc, char** argv);

    //! indicates if the regex has been matched in current line
    enum ReadResult { FR_GOOD, FR_BAD, FR_NO_MORE, FR_OPEN_FAILED };

    //! reads line and chechs if it maches regex, automatically opens files from fileList.
    //! Files that have been processed are removed from fileList.
    virtual ReadResult readLine(ResultLine& line) = 0;
    virtual ~FileReader();

};

#endif // FILEREADER_H
