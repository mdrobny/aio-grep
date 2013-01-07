#ifndef REGEXFINDER_H
#define REGEXFINDER_H

#include "resultline.h"
#include <string>

///
/// @class RegexFinder
/// @brief Abstract regex finder class.
/// This class specifies interface that all other regex classes should implement.
///
class RegexFinder
{
public:
    RegexFinder();

    ///
    /// @brief Executes regex matching operations on current line, based on std::string
    /// @param line line to be matched against
    /// @returns true if there has been a match, false otherwise
    ///
    virtual bool checkLine(ResultLine& line) = 0;

    ///
    /// @brief Executes regex matching operations on current line, based on char*. See \see{RegexFinder::checkLine}
    ///
    virtual bool checkLineChar(ResultLine& line) = 0;

    ///
    /// @brief Sets the current expression.
    /// @param r new expression
    ///
    virtual void setRegex(std::string r) = 0;
    virtual ~RegexFinder();
};

#endif // REGEXFINDER_H
