#include "fileinfo.h"

FileInfo::FileInfo(string name, aiocb * aioC) : fileName(name), aioControl(aioC), currentLine(0), next(-1), bufRest(""), eof(false)
{
}

FileInfo::~FileInfo()
{
    std::cout << eof << " UMIERAM!! Byłem FileInfo:(\n";
    free((void *) (aioControl->aio_buf));
    free(aioControl);
}
