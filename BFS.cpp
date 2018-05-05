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
    while (true)
    {
        ForwardSweep();
        BackwardSweep();

        if (!isConvergence())
        {
            break;
        }
    }
}

//======================================================================
void BFS::ForwardSweep()
{

}

//======================================================================
void BFS::BackwardSweep()
{
    vector<Node*> _pNodes;

    for (int i = 0; i < _nodes.size(); i++)
    {
        if (hasChild(_nodes[i]))
        {
            _pNodes.push_back(_nodes[i]);
        }
    }


}

//======================================================================
bool BFS::isConvergence()
{

}

//======================================================================
bool BFS::hasChild(const Node& node) const
{
    if (node->getChildNodes().size() == 0)
    {
        return false;
    }
    return true;
}
