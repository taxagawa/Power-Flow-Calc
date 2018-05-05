#ifndef __BFS_H__
#define __BFS_H__

#include "Node.h"
#include "Utility.h"

class BFS
{
public:
    BFS(const std::vector<Node*>& nodes, const DVEC& R, const DVEC& X);

    //計算する
    void CalcLoop();

private:
    //フォワード計算
    void ForwardSweep();

    //バックワード計算
    void BackwardSweep();

    //収束判定
    bool isConvergence();

    //子ノードを持つか
    bool hasChild(const Node* node) const;

private:
    std::vector<Node*> _nodes;

    const DVEC _R;

    const DVEC _X;
};

#endif //__BFS_H__
