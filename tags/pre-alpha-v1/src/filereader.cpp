#include "filereader.h"

FileReader::FileReader(int argc, char **argv, RegexFinder*& rf)
{
    regexFinder = rf;
    regexFinder->setRegex(std::string(argv[1]));

    for(int i = 2; i < argc; ++i)
    {
        std::string tmp(argv[i]);
        fileList.push_back(tmp);
    }
}

void FileReader::setRegexFinder(RegexFinder*& reg)
{
    regexFinder = reg;
}

FileReader::~FileReader()
{
}
