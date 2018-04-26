#include "Node.h"
#include <vector>

using namespace std;

//======================================================================
Node::Node():_id()
{
    _activePower   = 0.0;
    _reactivePower = 0.0;
}

//======================================================================
void Node::setId(const int& id)
{
    _id = id;
}

//======================================================================
int Node::getId() const
{
    return _id;
}
