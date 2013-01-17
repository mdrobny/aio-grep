#include "asynchronousfilereader.h"

AsynchronousFileReader::AsynchronousFileReader(int argc, char **argv, RegexFinder* rf)
    : currentFile(NULL), bufsize(10000) ,ln(new std::pair<char *, char *>), tmp(NULL), out(NULL)
{
    _argc = argc;
    _argv = argv;
    regexFinder = rf;
    int fileDesLimit = 100;
    int aioListSize = argc-2;
    if(argc - 2 > fileDesLimit)
        aioListSize = fileDesLimit;
    generalBuf = (char *) malloc(sizeof(char)*(bufsize+1)*(aioListSize));
    if (!generalBuf){
        cout << "allocation error. Files:" << aioListSize <<"\n";
        exit(-1);
    }
    aioList = (aiocb **) malloc((aioListSize)*sizeof(aiocb));
    bzero( (char *)aioList, (aioListSize) );
    int i;
    for (i = 2 ; i < aioListSize+2 ; ++i){
        // initializing aiocb for file
        aioList[i-2] = prepareAioStruct(argv[i], generalBuf+(i-2)*(bufsize+1), (aiocb *) malloc(sizeof(aiocb)) );
        FileInfo * file = new FileInfo(argv[i], aioList[i-2]);
        fileList.push_back(*file);
    }
    lastWaitingNo = i;
    int ret = lio_listio(LIO_NOWAIT, aioList, aioListSize, NULL );
    if (ret < 0)
        cout << "reading error in asynchronous reader\n";
}

aiocb * AsynchronousFileReader::prepareAioStruct(const char * filename, void * buf, aiocb * aio)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0){
        cout << "opening error in file" << filename <<"\n";
        return NULL;
    }
    bzero( (char *)aio, sizeof(struct aiocb) );
    aio->aio_buf = buf;
    aio->aio_fildes = fd;
    aio->aio_nbytes = bufsize;
    aio->aio_offset = 0;
    aio->aio_lio_opcode = LIO_READ;
    return aio;
}

void AsynchronousFileReader::switchFile(list<FileInfo>::iterator fi)
{
    aiocb * aio = fi->getControl();
    close(aio->aio_fildes);
    char * filename = _argv[lastWaitingNo];
    fi->setName(filename);
    int fd = open(filename , O_RDONLY);
    if (fd < 0){
        cout << "opening error in file" << filename <<"\n";
        return;
    }
    aio->aio_fildes = fd;
    aio->aio_offset = 0;
    aio_read(fi->getControl());
    fi->unsetEof();
    fi->zeroLine();
    fi->unsetRest();
    ++lastWaitingNo;
}

AsynchronousFileReader::~AsynchronousFileReader()
{
    free(aioList);
    free(generalBuf);
    delete ln;
}

FileReader::ReadResult AsynchronousFileReader::readLine(ResultLine &line)
{
    if(tmp){
        delete tmp;
        tmp = NULL;
    }
    if(out){
        delete out;
        out = NULL;
    }
    //if there is any 'opened' buffer to read => read from it
    if (currentFile){
        getLineFromBuf();
        if (currentFile->isEof()){
            currentFile = NULL;
        }
    }else {
        list<FileInfo>::iterator it;
        it = fileList.begin();
        while ( !fileList.empty() ){
            aiocb * ctrl = it->getControl();
            if ( aio_error(ctrl) == EINPROGRESS){
            }
            else{
               int ret = aio_return(ctrl);
               if (ret > 0){
                    if (it->isEof()){
                        currentFile = NULL;
                        if ( lastWaitingNo < _argc){
                            switchFile(it);
                            continue;
                        }else{
                            fileList.erase(it);
                        }
                        break;
                    }else{
                        openBuf(*it, ret);
                        getLineFromBuf();
                    }
                    break;
                } else {
                    if ( lastWaitingNo < _argc){
                       switchFile(it);
                    }else{
                       fileList.erase(it);
                       it = fileList.begin();
                       continue;
                    }
                }
                ++it;
                if (it == fileList.end())
                it = fileList.begin();
            }
        }
    }
    if(fileList.empty()){
        return FR_NO_MORE;
    }
    if (!ln->first ){
        currentFile = NULL;
        return FR_BAD;
    }else{
        line.setLine(ln->first,ln->second);
        line.clear();
        //poniższa linia wypisuje na ekran kolejne zwracane linie
        //std::cout << "\t" << string(ln->first,ln->second) << std::endl;
        if (regexFinder->checkLineChar(line) == true){
            std::string fName(currentFile->getName());
            line.setFilename(fName);
            out = new string;
            out->insert(0,ln->first,ln->second-ln->first);
            line.setLine(*out);
            line.setLineNum(currentFile->getCurrentLine());
            return FR_GOOD;
        } else {
            return FR_BAD;
        }
    }
}

void AsynchronousFileReader::openBuf(FileInfo & fInfo, int ret)
{
    currentFile = & fInfo;
    currentFile->setBufLength(ret);
    currentFile->setEnd((char *) currentFile->getControl()->aio_buf + ret);
    currentFile->setNext((char *) currentFile->getControl()->aio_buf - 1); // -1!?
    char * buf = (char *) currentFile->getControl()->aio_buf;
    buf[currentFile->getBufLength()] = '\0';
}

void AsynchronousFileReader::getLineFromBuf()
{
    char * buf = (char *) currentFile->getControl()->aio_buf;
    char del = '\n';
    char * next = currentFile->getNext();
    char * current = next + 1;
    char * end = currentFile->getEnd();
    next = strchr(current,del);

    currentFile->setNext(next);
    if(currentFile->getBufLength() < bufsize && !next ){
        currentFile->setEof();
    }
    //koniec buf
    if (!next){
        currentFile->setBufRest(current, end - current );
        if (!currentFile->isEof()){
            startNextRead(currentFile->getControl());
        }
        ln->first = NULL;
        ln->second = NULL;
    }else{
        if(currentFile->isRest()){
            tmp = new string();
            tmp->clear();
            tmp->insert(0,currentFile->getBufRest());
            tmp->append(current,next-current);
            ln->first = (char *) tmp->c_str();
            ln->second = (char *) tmp->c_str()+tmp->length();
        }else{
            ln->first = current;
            ln->second = next;
        }
        currentFile->plusLine();
    }

}

int AsynchronousFileReader::startNextRead(aiocb *aio)
{
    int offset = aio->aio_offset;
    aio->aio_offset = offset + bufsize;
    aio_read(aio);
    //std::cout << "aio_read\n";
}



