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

    //ノードの設定
    void buildNetwork();

    //getter
    std::vector<Node*> getNodes() const;

    DVEC getR() const;

    DVEC getX() const;

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

private:
    //作成したノードの集合
    std::vector<Node*> _nodes;

    int step;

    SVEC _link;

    SVEC _power;

    //レジスタンス行列
    DVEC _R;

    //リアクタンス行列
    DVEC _X;
};

#endif //__BFS_H__
