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

//======================================================================
void Node::setActivePower(double activePower)
{
    _activePower = activePower;
}

//======================================================================
double Node::getActivePower() const
{
    return _activePower;
}

//======================================================================
void Node::setReactivePower(double reactivePower)
{
    _reactivePower = reactivePower;
}

//======================================================================
double Node::getReactivePower() const
{
    return _reactivePower;
}
