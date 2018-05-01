#include "Node.h"
#include <vector>

using namespace std;

//======================================================================
Node::Node(int id)
{
    _id         = id;

    _activePower   = 0.0;
    _reactivePower = 0.0;

    _amplitude = 0.0;
    _angle     = 0.0;
}

//======================================================================
int Node::getId() const
{
    return _id;
}

//======================================================================
void Node::setParentNode(int parentNode)
{
    _parentNode = parentNode;
}

//======================================================================
int Node::getParentNode() const
{
    return _parentNode;
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

//======================================================================
void Node::setAmplitude(double amplitude)
{
    _amplitude = amplitude;
}

//======================================================================
double Node::getAmplitude() const
{
    return _amplitude;
}

//======================================================================
void Node::setAngle(double angle)
{
    _angle = angle;
}

//======================================================================
double Node::getAngle() const
{
    return _angle;
}
