#include "asynchronousfilereader.h"

AsynchronousFileReader::AsynchronousFileReader(int argc, char **argv, RegexFinder* rf) : currentFile(NULL), bufsize(200)
{
    regexFinder = rf;
    aioList = (aiocb **) malloc((argc-2)*sizeof(aiocb *));
    bzero( (char *)aioList, (argc-2) );
    for (int i = 2 ; i < argc ; ++i){
        //! initializing aiocb for file
        aioList[i-2] = (aiocb *) malloc( sizeof(aiocb));
        int fd = open(argv[i], O_RDONLY);
        if (fd < 0){
            cout << "opening error in file" << argv[i] <<"\n";
            continue;
        }
        bzero( (char *)aioList[i-2], sizeof(struct aiocb) );
        aioList[i-2]->aio_buf = new char[bufsize];
        if (!aioList[i-2]->aio_buf){
            cout << "allocation error in file" << argv[i] <<"\n";
            continue;
        }
        aioList[i-2]->aio_fildes = fd;
        aioList[i-2]->aio_nbytes = bufsize;
        aioList[i-2]->aio_offset = 0;
        aioList[i-2]->aio_lio_opcode = LIO_READ;

        FileInfo * file = new FileInfo(argv[i], aioList[i-2]);
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
        //std::cout << "czyta z otwartego\n";
        string tmp = getLineFromBuf();
        if (tmp == ">>eob<<"){
            return FR_BAD;
        }
        line.setLine(tmp);
        //std::cout << "eof = " << currentFile->isEof() << std::endl;
        if (currentFile->isEof()){
            cout << "eof:  " << currentFile->isEof() << "  \n";
            currentFile = NULL;
        }
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
            //cout << "\t iter:"<< ++i << "\n";
        if ( aio_error(ctrl) == EINPROGRESS){
            continue;
        }
        else{
           int ret = aio_return(it->getControl());
           if (ret > 0){
                //cout << it->getName() << " " << ret << " w pętli \n";
                string tmp = openBuf(*it, ret);
                if (tmp == ">>eob<<")
                    return FR_BAD;
                line.setLine(tmp);
                line.setFilename(currentFile->getName());
                //if eof => eof, erasing file from list
                if (it->isEof()){
                    fileList.erase(it);
                    currentFile = NULL;
                }
                if (regexFinder->checkLine(line) == true){
                    return FR_GOOD;
                } else {
                    return FR_BAD;
                }
            } else {
                //delete &(*it);
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

string AsynchronousFileReader::openBuf(FileInfo & fInfo, int ret)
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
    //std::cout << "getLineFromBuf(): " << current << "  " << next << endl;
    if(currentFile->getBufLength() == next && next < bufsize){
        //std::cout << "set eof next:" << next << " bufL: " << currentFile->getBufLength() << std::endl;
        currentFile->setEof();
        //std::cout << currentFile->isEof() <<endl;
    }
    if (next == string::npos || next > bufsize){
        //std::cout << "koniec buffora\n";
        string restLine = buf.substr( current, bufsize );
        currentFile->setBufRest(restLine);
        currentFile->setNext(-1);
        //initializing next aio reading
        startNextRead(currentFile->getControl());
        currentFile = NULL;
        return ">>eob<<";
    }else{
        string retLine = buf.substr( current, next - current );
        currentFile->plusLine();
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
