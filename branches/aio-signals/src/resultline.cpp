#include "resultline.h"

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


void ResultLine::addOccurence(int_pair_t occ)
{
    occurences.push_back(occ);
}


void ResultLine::setLineNum(int n)
{
    lineNum = n;
}


int_pair_t ResultLine::getOccurence(int which) const
{
    return occurences[which];
}


int ResultLine::getLineNum() const
{
    return lineNum;
}

std::string ResultLine::getFilename()
{
    return filename;
}


void ResultLine::setFilename(std::string &filename)
{
    this->filename = filename;
}

int ResultLine::getNumberOfOccurences()
{
    return occurences.size();
}

void ResultLine::clear()
{
    occurences.clear();
    line.clear();
    lineNum = 0;
    filename = "";
}
