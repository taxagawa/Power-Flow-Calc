#ifndef __BFSCALC_H__
#define __BFSCALC_H__

#include "FileIO.h"

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
    std::vector< std::vector<std::string> > _linkInfo;

    //初期電力情報
    std::vector< std::vector<std::string> > _initPower;

};

#endif //__BFSCALC_H__
