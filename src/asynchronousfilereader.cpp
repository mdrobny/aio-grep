#include "asynchronousfilereader.h"

AsynchronousFileReader::AsynchronousFileReader(int argc, char **argv, RegexFinder*& rf)
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
