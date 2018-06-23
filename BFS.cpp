#include "BFS.h"
#include "Node.h"
#include "Utility.h"
#include <iostream>
#include <vector>

using namespace std;

namespace
{
    const double EPS = 2.2943E-11;
}

//======================================================================
BFS::BFS(const vector<Node*>& nodes, const DVEC& R, const DVEC& X): _R(R), _X(X)
{
    _nodes = nodes;
}

//======================================================================
void BFS::CalcLoop()
{
    //cout << "a1" << endl;
    int beginId;

    for (int i = _nodes.size()-1; i >= 0; i--)
    {
        //begin nodeが複数ある場合は修正が必要
        if (_nodes[i]->getParentNode() == 0)
        {
            beginId = i;
            break;
        }
    }

    vector<Node*> pNodes;
    for (int i = 0; i < _nodes.size(); i++)
    {
        //子ノードを持つが孫ノードを持たないノードを格納
        //これらはBackward計算のスタートのノードとなる
        if (hasChild(_nodes[i]))
        {
            if (!(hasGrandchild(_nodes[i])))
            {
                pNodes.push_back(_nodes[i]);
                //cout << _nodes[i]->getId() << endl;
            }
        }
    }

    int step = 1;
    while (true)
    {
        cout << "Calculation Step: " << step << endl;
        step++;

        ForwardSweep(beginId);
        BackwardSweep(pNodes);

        if (isConvergence())
        {
            break;
        }
    }
}

//======================================================================
void BFS::ForwardSweep(int beginId)
{
    vector<int> id;

    id.push_back(beginId);

    while (id.size() != 0)
    {
        
    }

}

//======================================================================
void BFS::BackwardSweep(vector<Node*> _pNodes)
{

}

//======================================================================
bool BFS::isConvergence()
{
    return true;
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
    //cout << node->getId() << ":";

    int p = 0;
    int q = node->getChildNodes().size();
    //cout << "q:" << q << " ";

    //子ノードを持つ前提で使用
    vector<int>::const_iterator itEnd = node->getChildNodes().end();

    for (vector<int>::const_iterator ite = node->getChildNodes().begin(); ite != itEnd; ++ite)
    {
        //cout << *ite << ",";
        if (!(hasChild(_nodes[*ite-1])))
        {
            p++;
        }
    }

    //cout << " p:" << p << endl;
    if (p == q)
    {
        return false;
    } 
    else 
    {
        return true;
    }
}
