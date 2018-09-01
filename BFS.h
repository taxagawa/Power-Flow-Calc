#ifndef __BFS_H__
#define __BFS_H__

#include "Node.h"
#include "Utility.h"
#include <string>
#include <vector>

class BFS
{
public:
    BFS(const SVEC& _linkInfo, const SVEC& _initPower);

    //計算する
    void CalcLoop();

private:
    //Forward計算
    void ForwardSweep(int beginId);

    //Backward計算
    void BackwardSweep(int id);

    //再帰関数を用いた深さ優先探索
    //void DFS(int id, int visited[]);

    //子ノードが訪問済みかどうかを調べる
    bool checkChildrenVisited(int id, int visited[]);

    //収束判定
    bool isConvergence();

    //子ノードを持つか
    bool hasChild(const Node* node) const;

    //結果を格納する
    void setOutput();

public:
    //ノードの設定
    void buildNetwork();

    //getter
    std::vector<Node*> getNodes() const;

    DVEC getR() const;

    DVEC getX() const;

    DVEC getOutputAm() const;

    DVEC getOutputTh() const;

    int getStepNum() const;

private:
    //作成したノードの集合
    std::vector<Node*> _nodes;

    int step;

    //最大step数
    int limit;

    SVEC _link;

    SVEC _power;

    //レジスタンス行列
    DVEC _R;

    //リアクタンス行列
    DVEC _X;

    //結果(振幅)を格納した行列
    DVEC outputAm;

    //結果(位相)を格納した行列
    DVEC outputTh;
};

#endif //__BFS_H__
