#include "fileinfo.h"

FileInfo::FileInfo(string name, aiocb * aioC = NULL)
    : fileName(name), aioControl(aioC), currentLine(0), next(-1), bufRest(""), eof(false)
{
}

FileInfo::~FileInfo()
{
    close(aioControl->aio_fildes);
    free((void *) (aioControl->aio_buf));
    free(aioControl);
}
