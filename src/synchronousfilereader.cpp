#include "synchronousfilereader.h"

SynchronousFileReader::SynchronousFileReader(int argc, char** argv) :
    FileReader(argc, argv),
    currentFile(0),
    currentLine(0)
{
}

FileReader::ReadResult SynchronousFileReader::readLine(ResultLine &line)
{
    if(!currentFile.is_open())
    {
        if(fileList.size() == 0)
            return FR_NO_MORE;
        currentFilename = fileList.back();
        fileList.pop_back();
        currentFile.open(currentFilename.c_str());
        currentLine = 0;
    }

    line.setFilename(currentFilename);
    std::string tmp_line;
    std::getline(currentFile, tmp_line);
    line.setLine(tmp_line);
    line.setLineNum(++currentLine);
    if(!currentFile.good())
    {
        currentFile.close();
    }
    if(strstr(line.getLine().c_str(), regex.c_str()) != 0)
        return FR_GOOD;
    else return FR_BAD;
}
