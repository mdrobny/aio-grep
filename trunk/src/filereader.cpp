#include "filereader.h"

FileReader::FileReader(char **argv, int argc)
{
    for(int i = 1; i < argc; ++i)
    {
        std::string tmp(argv[i]);
        fileList.push_back(tmp);
    }
}
