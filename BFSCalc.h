#ifndef __BFSCALC_H__
#define __BFSCALC_H__

#include "FileIO.h"
#include "Utility.h"

class BFSCalc
{
public:
    BFSCalc();

    ~BFSCalc();

    //入力ファイルのセッティング
    void dataSetting(int argc, char** argv);

private:
    FileIO* _fileIO;

    //リンク情報
    SVEC _linkInfo;

    //初期電力情報
    SVEC _initPower;

};

#endif //__BFSCALC_H__
