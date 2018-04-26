#ifndef __BFSCALC_H__
#define __BFSCALC_H__

#include "FileIO.h"

class BFSCalc
{
public:
    BFSCalc();

    ~BFSCalc();

    void dataSetting(int argc, char** argv);

private:
    FileIO* _fileIO;


};

#endif //__BFSCALC_H__
