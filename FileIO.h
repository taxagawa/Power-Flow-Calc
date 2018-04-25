#ifndef __FILEIO_H__
#define __FILEIO_H__

#include "FileIOManager.h"

class FileIO
{
public:
    bool pathSetting(int argc, char** argv);

private:
    FileIOManager* fileIOm;
};

#endif //__FILEIO_H__
