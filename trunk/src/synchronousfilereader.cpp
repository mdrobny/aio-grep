#include "synchronousfilereader.h"

SynchronousFileReader::SynchronousFileReader(int argc, char** argv) :
    FileReader(argc, argv),
    currentFile(0),
    currentLine(0)
{
}

ResultLine SynchronousFileReader::readLine()
{
    ResultLine line;
    if(!currentFile.is_open())
    {
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
    return line;
}
