#include "fileinfo.h"

FileInfo::FileInfo(char * name, aiocb * aioC = NULL)
    : fileName(name), aioControl(aioC), currentLine(0), eof(false), bufRest(string()), isBufRest(0)
{
}

FileInfo::~FileInfo()
{
    close(aioControl->aio_fildes);
    free(aioControl);
}
