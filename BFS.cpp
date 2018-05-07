#include "BFS.h"
#include "Node.h"
#include "Utility.h"
#include <iostream>
#include <vector>

using namespace std;

namespace
{
    const double IVAL = 2.2943E-11;
}

//======================================================================
BFS::BFS(const vector<Node*>& nodes, const DVEC& R, const DVEC& X): _R(R), _X(X)
{
    _nodes = nodes;
}

//======================================================================
void BFS::CalcLoop()
{
    int beginId;
    for (int i = _nodes.size()-1; i < 0; i--)
    {
        if (_nodes[i]->getParentNode() == 0)
        {
            beginId = i;
            break;
        }
    }

    vector<Node*> _pNodes;
    for (int i = 0; i < _nodes.size(); i++)
    {
        //子ノードを持つが孫ノードを持たないノードを格納
        //これらはBackward計算のスタートのノードとなる
        if (hasChild(_nodes[i]) && !(hasGrandchild(_nodes[i])))
        {
            _pNodes.push_back(_nodes[i]);
        }
    }

    int step = 1;
    while (true)
    {
        cout << "Calculation Step: " << step << endl;
        step++;

        ForwardSweep(beginId);
        BackwardSweep(_pNodes);

        if (!isConvergence())
        {
            break;
        }
    }
}

//======================================================================
void BFS::ForwardSweep(int beginId)
{

}

//======================================================================
void BFS::BackwardSweep(vector<Node*> _pNodes)
{

}

//======================================================================
bool BFS::isConvergence()
{
    return false;
}

//======================================================================
bool BFS::hasChild(const Node* node) const
{
    if (node->getChildNodes().size() == 0)
    {
        return false;
    }
    return true;
}

//======================================================================
bool BFS::hasGrandchild(const Node* node) const
{
    //debug
    cout << node->getId() << endl;

    //子ノードを持つ前提で使用
    vector<int>::const_iterator itEnd = node->getChildNodes().end();

    for (vector<int>::const_iterator ite = node->getChildNodes().begin(); ite != itEnd; ++ite)
    {
        //debug
        cout << *ite << endl;

        if (!(hasChild(_nodes[*ite])))
        {
            return false;
        }
    }
    return true;
}
