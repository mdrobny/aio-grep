#include "asynchronousfilereader.h"

AsynchronousFileReader::AsynchronousFileReader(int argc, char **argv, RegexFinder* rf)
    : currentFile(NULL), bufsize(1000)
{
    _argc = argc;
    _argv = argv;
    regexFinder = rf;
    int fileDesLimit = 1021;
    int aioListSize = argc-2;
    if(argc - 2 > fileDesLimit)
        aioListSize = fileDesLimit;
    aioList = (aiocb **) malloc((aioListSize)*sizeof(aiocb *));
    bzero( (char *)aioList, (aioListSize) );
    int i;
    for (i = 2 ; i < aioListSize+2 ; ++i){
        //! initializing aiocb for file
        aioList[i-2] = prepareAioStruct(argv[i]);
        FileInfo * file = new FileInfo(argv[i], aioList[i-2]);
        fileList.push_back(*file);
    }
    cout << "konstr\n";
    lastWaitingNo = i;
    int ret = lio_listio(LIO_NOWAIT, aioList, aioListSize, NULL );
    if (ret < 0)
        cout << "reading error in asynchronous reader\n";
    cout << "ENDkonstr\n";
}

aiocb * AsynchronousFileReader::prepareAioStruct(const char * filename)
{
    aiocb * aio = (aiocb *) malloc( sizeof(aiocb));
    int fd = open(filename, O_RDONLY);
    if (fd < 0){
        cout << "opening error in file" << filename <<"\n";
        return NULL;
    }
    bzero( (char *)aio, sizeof(struct aiocb) );
    aio->aio_buf = new char[bufsize + 1];
    if (!aio->aio_buf){
        cout << "allocation error in file" << filename <<"\n";
        return NULL;
    }
    aio->aio_fildes = fd;
    aio->aio_nbytes = bufsize;
    aio->aio_offset = 0;
    aio->aio_lio_opcode = LIO_READ;
    return aio;
}

AsynchronousFileReader::~AsynchronousFileReader()
{
    free(aioList);
}

FileReader::ReadResult AsynchronousFileReader::readLine(ResultLine &line)
{
    //if there is any 'opened' buffer to read => read from it
    if (currentFile){
        //std::cout << "czyta z otwartego\n";
        string tmp = getLineFromBuf();
        if (tmp == ">>eob<<"){
            return FR_BAD;
        }
        line.setLine(tmp);
        //std::cout << "eof = " << currentFile->isEof() << std::endl;
        if (currentFile->isEof()){
            //cout << "eof:  " << currentFile->isEof() << "  \n";
            currentFile = NULL;
        }
        if (regexFinder->checkLine(line) == true){
            line.clear();
            std::string fName(currentFile->getName());
            line.setFilename(fName);
            line.setLineNum(currentFile->getCurrentLine());
            return FR_GOOD;
        } else {
            return FR_BAD;
        }
    }else {
//else find aiocb which completed reading, and 'open' this buffer
        list<FileInfo>::iterator it;
        it = fileList.begin();
        int i = 0;
        while ( !fileList.empty() ){
            aiocb * ctrl = it->getControl();
            if ( aio_error(ctrl) == EINPROGRESS){
                //cout << ++i << "\t";
            }
            else{
               int ret = aio_return(it->getControl());
               if (ret > 0){
                    //cout << it->getName() << " " << ret << " w pętli \n";
                    string tmp = openBuf(*it, ret);
                    if (tmp == ">>eob<<")
                        return FR_BAD;
                    if (regexFinder->checkLine(line) == true){
                        line.clear();
                        std::string fName(currentFile->getName());
                        line.setFilename(fName);
                        line.setLineNum(currentFile->getCurrentLine());
                        line.setLine(tmp);
                    }
                    //if eof => eof, erasing file from list and add another one if exist
                    if (it->isEof()){
                        //cout << "EOF\t" << fileList.size() << " \t";
                        fileList.erase(it);
                        currentFile = NULL;
                        if ( lastWaitingNo < _argc){
                            aiocb * aioStruct = prepareAioStruct(_argv[lastWaitingNo]);
                            if(aioStruct){
                                FileInfo * file = new FileInfo(_argv[lastWaitingNo], aioStruct);
                                fileList.push_back(*file);
                                aio_read(aioStruct);
                                ++lastWaitingNo;
                            }
                        }
                    }
                    if (regexFinder->checkLine(line) == true){
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
}

string AsynchronousFileReader::openBuf(FileInfo & fInfo, int ret)
{
    currentFile = & fInfo;
    currentFile->setBufLength(ret);
    currentFile->setEnd((char *) currentFile->getControl()->aio_buf + ret);
    currentFile->setNext((char *) currentFile->getControl()->aio_buf - 1);
    return getLineFromBuf();
}

string AsynchronousFileReader::getLineFromBuf()
{
    char * buf = (char *) currentFile->getControl()->aio_buf;
    buf[bufsize] = '\0';
    char del = '\n';
    char * next = currentFile->getNext();
    char * current = next + 1;
    char * end = currentFile->getEnd();
    //next = buf.find_first_of( del, current );
    next = strchr(current,del);

    currentFile->setNext(next);
    if(currentFile->getBufLength() < bufsize && next == end){
        //cout << "\nsetEOF\n";
        currentFile->setEof();
    }
    //koniec buf
    if (!next){
        currentFile->setBufRest(current, end - current );
        if (!currentFile->isEof())
            startNextRead(currentFile->getControl());
        currentFile = NULL;
        return ">>eob<<";
    }else{
        std::string retLine("");
        if(currentFile->isRest()){
            retLine.insert(0,currentFile->getBufRest());
        }
        retLine.append(current,next-current);
        currentFile->plusLine();
        //poniższa linia wypisuje na ekran kolejne zwracane linie
        //std::cout << currentFile->getCurrentLine() << "\t" << retLine << std::endl;
        return retLine;
    }

}

int AsynchronousFileReader::startNextRead(aiocb *aio)
{
    int offset = aio->aio_offset;
    aio->aio_offset = offset + bufsize;
    aio_read(aio);
    //std::cout << "aio_read\n";
}



