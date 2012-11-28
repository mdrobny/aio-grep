#include "asynchronousfilereader.h"

AsynchronousFileReader::AsynchronousFileReader(int argc, char **argv, RegexFinder* rf) : currentFile(NULL), bufsize(200)
{
    regexFinder = rf;
    aioList = (aiocb **) malloc((argc-2)*sizeof(aiocb *));
    bzero( (char *)aioList, (argc-2) );
    for (int i = 2 ; i < argc ; ++i){
        //! initializing aiocb for file
        aiocb * fileC = (aiocb *) malloc( sizeof(aiocb));
        int fd = open(argv[i], O_RDONLY);
        if (fd < 0){
            cout << "opening error in file" << argv[i] <<"\n";
            continue;
        }
        bzero( (char *)fileC, sizeof(struct aiocb) );
        fileC->aio_buf = new char[bufsize];
        if (!fileC->aio_buf){
            cout << "allocation error in file" << argv[i] <<"\n";
            continue;
        }
        fileC->aio_fildes = fd;
        fileC->aio_nbytes = bufsize;
        fileC->aio_offset = 0;
        fileC->aio_lio_opcode = LIO_READ;

        aioList[i-2] = fileC;
        FileInfo * file = new FileInfo(argv[i], fileC);
        fileList.push_back(*file);
    }
    int ret = lio_listio(LIO_NOWAIT, aioList, argc-2, NULL );
    if (ret < 0)
        cout << "reading error in asynchronous reader\n";
}

AsynchronousFileReader::~AsynchronousFileReader()
{
    free(aioList);
}

FileReader::ReadResult AsynchronousFileReader::readLine(ResultLine &line)
{
    //if there is any 'opened' buffer to read => read from it
    if (currentFile != NULL){
        string tmp = getLineFromBuf();
        line.setLine(tmp);
        if (currentFile->isEof())
            delete currentFile;
        if (regexFinder->checkLine(line) == true){
            line.setFilename(currentFile->getName());
            return FR_GOOD;
        } else {
            return FR_BAD;
        }
    }

    //else find aiocb which completed reading, and 'open' this buffer
    list<FileInfo>::iterator it;
    it = fileList.begin();
    int i = 0;
    while ( !fileList.empty() ){
        aiocb * ctrl = it->getControl();
        if ( aio_error(ctrl) == EINPROGRESS){
            cout << ++i << "\n";
            continue;
        }
        else{
            cout << "w pętli znalazło przeczytany aiocb\n";
            if (int ret = aio_return(ctrl) > 0){
                cout << it->getName() << " " << ret << " w pętli \n";
                string tmp = openBuf(*it, ret);
                line.setLine(tmp);
                line.setFilename(currentFile->getName());
                cout << " w pętli po openBuf()\n";
                //if ret < bufsize => eof, erasing file from list
                if (ret < bufsize){
                    fileList.erase(it);
                }
                if (regexFinder->checkLine(line) == true){
                    return FR_GOOD;
                } else {
                    return FR_BAD;
                }
            } else {
                cout << "usuwa\n";
                delete &(*it);
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
        if(currentFile->getBufLength() < bufsize)
            currentFile->setEof();
        else {
            //initializing next aio reading
            aiocb * aio = currentFile->getControl();
            int offset = aio->aio_offset;
            aio->aio_offset = offset + bufsize;
            bzero( (char *)&(aio->aio_buf), sizeof(char)*bufsize );
            aio_read(aio);
        }
        currentFile = NULL;
    }else{
        currentFile->plusLine();
        return buf.substr( current, next - current );
    }
}
