#include "asynchronousfilereader.h"

AsynchronousFileReader::AsynchronousFileReader(int argc, char **argv, RegexFinder* rf) : currentFile(NULL), bufsize(200)
{
    argc = 4;
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
    int ret = lio_listio(LIO_WAIT, aioList, argc-2, NULL );
    if (ret < 0)
        cout << "reading error in asynchronous reader\n";


    //////debug
    list<FileInfo>::iterator it;
    for ( it = fileList.begin() ; it !=fileList.end() ; ++it){
        aiocb * ctrl = it->getControl();
        if ( aio_error( ctrl ) == EINPROGRESS ){}
        else{
            if ((ret = aio_return( ctrl )) > 0) {
                cout << &(*it) << " <- adres aiocb czytanych znaków-> "<< ret << endl <<(char *) ctrl->aio_buf << endl;
              } else {
                cout << "failed";
              }
        }
    }
    ///////end
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
            cout << "\t iter:"<< ++i << "\n";
        if ( aio_error(ctrl) == EINPROGRESS){
            continue;
        }
        else{
           if (int ret = aio_return(it->getControl()) > 0){
               cout<< ctrl << " <- adres aiocb fd->" << ctrl->aio_fildes << " czytanych znaków->" << ret << "\nw pętli znalazło przeczytany aiocb\n";
                if(ret == 1){
                    ++it;
                    continue;
                }
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
