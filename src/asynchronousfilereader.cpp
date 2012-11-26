#include "asynchronousfilereader.h"

AsynchronousFileReader::AsynchronousFileReader(int argc, char **argv, RegexFinder*& rf) : currentFile(NULL), regexFinder(rf)
{
    aiocb * list[argc-2];
    bzero( (char *)list, sizeof(list) );

    for (int i = 2 ; i < argc ; ++i){
        //! initializing aiocb for file
        aiocb fileC;
        int fd = open(argv[i], O_RDONLY);
        if (fd < 0){
            cout << "opening error in file" << argv[i] <<"\n";
            continue;
        }
        bzero( (char *)&fileC, sizeof(struct aiocb) );
        fileC.aio_buf = new char[bufsize];
        if (!fileC.aio_buf){
            cout << "allocation error in file" << argv[i] <<"\n";
            continue;
        }
        fileC.aio_fildes = fd;
        fileC.aio_nbytes = bufsize;
        fileC.aio_offset = 0;
        fileC.aio_lio_opcode = LIO_READ;

        list[i-2] = &fileC;
        FileInfo file(argv[i], &fileC);
        fileList.push_back(file);
    }
    int ret = lio_listio(LIO_NOWAIT, list, argc-2, NULL );
    if (ret < 0)
        cout << "reading error in asynchronous reader\n";
}

FileReader::ReadResult AsynchronousFileReader::readLine(ResultLine &line)
{
    //jeśli jest jakiś otwarty bufor
    if (currentFile != NULL){
        string tmp = getLineFromBuf();
        line.setLine(tmp);
        if (regexFinder->checkLine(line) == true){
            line.setFilename(currentFile->getName());
            return FR_GOOD;
        } else {
            return FR_BAD;
        }
    }

    //jeśli nie, to szuka pierwszego skończonego
    list<FileInfo>::iterator it;
    it = fileList.begin();
    while ( !fileList.empty() ){
        aiocb * ctrl = it->getControl();
        if ( aio_error(ctrl) == EINPROGRESS){
        }
        else{
            if (int ret = aio_return(ctrl) > 0){
                string tmp = openBuf(*it, ret);
                line.setLine(tmp);
                if (regexFinder->checkLine(line) == true){
                    line.setFilename(currentFile->getName());
                    return FR_GOOD;
                } else {
                    return FR_BAD;
                }
            } else {
                fileList.erase(it);
                it = fileList.begin();
            }
        }
        ++it;
        if (it == fileList.end())
            it = fileList.begin();
    }
    return FR_NO_MORE;
}

string AsynchronousFileReader::openBuf(FileInfo fInfo, int ret)
{
    currentFile = & fInfo;
    currentFile->setBufLength(ret);
    return getLineFromBuf();
}

string AsynchronousFileReader::getLineFromBuf()
{
    //string o wielkości równej ilości znaków przeczytanych przez aio
    string buf( (char *) currentFile->getControl()->aio_buf, currentFile->getBufLength());
    buf = currentFile->getBufRest() + buf;
    string del = "\n";
    size_t next = currentFile->getNext();
    size_t current = next + 1;
    next = buf.find_first_of( del, current );
    currentFile->setNext(next);
    if (next == string::npos){
        currentFile->setBufRest(buf.substr( current, bufsize ));
        currentFile->setNext(-1);
        currentFile = NULL;
    }else{
        currentFile->plusLine();
        return buf.substr( current, next - current );
    }
}
