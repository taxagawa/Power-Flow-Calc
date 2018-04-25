#ifndef __PREPROC_H__
#define __PREPROC_H__

#include "FileIO.h"

class PreProc
{
public:
    void init(int argc, char** argv);

private:
    FileIO* fileIO;
};

#endif //__PREPROC_H__
