#ifndef __BFSCALC_H__
#define __BFSCALC_H__

#include "FileIO.h"
#include "Node.h"
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

    //ノードの集合
    std::vector<Node*> _nodes;

    //レジスタンス行列
    DVEC _R;

    //リアクタンス行列
    DVEC _X;

    //振幅結果行列
    DVEC outputAm;

    //位相結果行列
    DVEC outputTh;

    //最終ステップ数
    int finalStepNum;

};

#endif //__BFSCALC_H__
