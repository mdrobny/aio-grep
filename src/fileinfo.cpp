#include "fileinfo.h"

FileInfo::FileInfo(string name, aiocb * aioC) : fileName(name), aioControl(aioC), currentLine(0), next(-1), bufRest("")
{
}