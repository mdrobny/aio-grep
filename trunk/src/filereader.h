#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <string>
#include <vector>
#include "resultline.h"
#include "regexfinder.h"

///
/// @class FileReader
/// @brief Abstract file reader class.
/// Specifies a common interface for all file readers implementations.
///
class FileReader
{

protected:
    ///
    /// @brief Pointer to regex finder object.
    ///
    RegexFinder* regexFinder;

public:

    ///
    /// @brief Empty constructor.
    ///
    FileReader(){}

    ///
    /// @brief Initializes object to perform reading.
    /// @param argc number of files
    /// @param argv array of filenames
    /// @param rf pointer to initialized RegexFinder object
    ///
    FileReader(int argc, char** argv, RegexFinder*& rf);

    /// Indicates the status of file reader
    enum ReadResult { FR_GOOD, /// Line has been read and there is a match
                      FR_BAD,  /// Line has been read and there is no match
                      FR_NO_MORE, /// There are no more lines in a file
                      FR_OPEN_FAILED /// Could not open current file
                    };

    ///
    /// Reads line and checks if it maches regex, automatically opens next files.
    /// @param line reference to object that will hold currently read line
    /// @returns status from ReadResult enum.
    ///
    virtual ReadResult readLine(ResultLine& line) = 0;

    ///
    /// Sets the current regex finder.
    /// @param reg pointer to new RegexFinder object
    ///
    virtual void setRegexFinder(RegexFinder *&reg);
    
    virtual ~FileReader();

};

#endif // FILEREADER_H
