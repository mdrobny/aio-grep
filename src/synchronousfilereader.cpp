#include "synchronousfilereader.h"

SynchronousFileReader::SynchronousFileReader(int argc, char** argv, RegexFinder *&rf) :
    FileReader(argc, argv, rf),
    currentFile(0),
    currentLine(0)
{
    for(int i = 2; i < argc; ++i)
        {
            std::string tmp(argv[i]);
            fileList.push_back(tmp);
        }
}

FileReader::ReadResult SynchronousFileReader::readLine(ResultLine &line)
{
    line.clear();
    if(!currentFile.is_open())
    {
        if(fileList.size() == 0)
            return FR_NO_MORE;
        currentFilename = fileList.back();
        fileList.pop_back();
        currentFile.open(currentFilename.c_str());
        if(!currentFile.good()) {
            currentFile.close();
            return FR_OPEN_FAILED;
         }
        currentLine = 0;
    }

    std::string tmp_line;
    std::getline(currentFile, tmp_line);
    line.setFilename(currentFilename);
    line.setLine(tmp_line);
    line.setLineNum(++currentLine);
    if(!currentFile.good())
    {
        currentFile.close();
    }
    if(regexFinder->checkLine(line) == true)
        return FR_GOOD;
    else return FR_BAD;
}
