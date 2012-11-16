#include "ResultLine.h"

ResultLine::ResultLine()
{
}


void ResultLine::setLine(std::string &str)
{
    line = str;
}


void ResultLine::appendToLine(std::string &str)
{
    line.append(str.c_str());
}


std::string ResultLine::getLine() const
{
    return line;
}


void ResultLine::addOccurence(std::pair<int, int> occ)
{
    occrurences.push_back(occ);
}


void ResultLine::setLineNum(int n)
{
    lineNum = n;
}


std::pair<int, int> ResultLine::getOccurence(int which) const
{
    return occurences.at(which);
}


int ResultLine::getLineNum() const
{
    return lineNum;
}
