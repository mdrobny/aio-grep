#include "resultline.h"

ResultLine::ResultLine()
{
}

void ResultLine::setLine(const std::string &str)
{
    line = str;
}


const std::string& ResultLine::getLine() const
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


const std::pair<int, int>& ResultLine::getOccurence(int which) const
{
    return occurences[which];
}


int ResultLine::getLineNum() const
{
    return lineNum;
}

const std::string& ResultLine::getFilename() const
{
    return filename;
}

void ResultLine::setFilename(const std::string &filename)
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
    //line = "";
    lineNum = 0;
    filename = "";
}


void ResultLine::setLine(char *b, char *e)
{
    begin = b;
    end = e;
}

char * ResultLine::getBeginLine()
{
    return begin;
}

char * ResultLine::getEndLine()
{
    return end;
}
