#include "Node.h"
#include <vector>
#include <iostream>

using namespace std;

//======================================================================
Node::Node(int id)
{
    _id = id;

    _activePower    = 0.0;
    _dActivePower   = 0.0;
    _pActivePower   = 0.0;
    _reactivePower  = 0.0;
    _dReactivePower = 0.0;
    _pReactivePower = 0.0;

    childNodes.reserve(10);

    _amplitude = 0.0;
    _angle     = 0.0;
}

//======================================================================
Node::Node(const Node &node):_id(node._id),_activePower(node._activePower),_dActivePower(node._dActivePower),_pActivePower(node._pActivePower),_reactivePower(node._reactivePower),_dReactivePower(node._dReactivePower),_pReactivePower(node._pReactivePower),_amplitude(node._amplitude),_angle(node._angle),childNodes(node.childNodes)
{
    //cout << "コピーコンストラクタ" << cout;
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
void Node::setChildNodes(const int& id)
{
    this->childNodes.push_back(id);
}

//======================================================================
std::vector<int> Node::getChildNodes() const
{
    return childNodes;
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
void Node::setDefaultActivePower(double dActivePower)
{
    _dActivePower = dActivePower;
}

//======================================================================
double Node::getDefaultActivePower() const
{
    return _dActivePower;
}

//======================================================================
void Node::setPreActivePower(double pActivePower)
{
    _pActivePower = pActivePower;
}

//======================================================================
double Node::getPreActivePower() const
{
    return _pActivePower;
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
void Node::setDefaultReactivePower(double dReactivePower)
{
    _dReactivePower = dReactivePower;
}

//======================================================================
double Node::getDefaultReactivePower() const
{
    return _dReactivePower;
}

//======================================================================
void Node::setPreReactivePower(double pReactivePower)
{
    _pReactivePower = pReactivePower;
}

//======================================================================
double Node::getPreReactivePower() const
{
    return _pReactivePower;
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
void Node::setPreAmplitude(double preAmplitude)
{
    _preAmplitude = preAmplitude;
}

//======================================================================
double Node::getPreAmplitude() const
{
    return _preAmplitude;
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
