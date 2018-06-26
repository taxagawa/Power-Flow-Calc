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
    //Forward計算
    void ForwardSweep(int beginId);

    //Backward計算
    void BackwardSweep(std::vector<int> _pNodeIdx);

    //収束判定
    bool isConvergence();

    //子ノードを持つか
    bool hasChild(const Node* node) const;

    //孫ノードを持つか
    bool hasGrandchild(const Node* node) const;

    void returnEndPoints(std::vector<int>& tmpNodes, std::vector<Node*> nodes);

private:
    std::vector<Node*> _nodes;

    const DVEC _R;

    const DVEC _X;
};

#endif //__BFS_H__
