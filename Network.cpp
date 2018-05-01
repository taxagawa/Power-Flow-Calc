#include "Network.h"
#include "Node.h"
#include "Utility.h"
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//======================================================================
Network::Network(SVEC _linkInfo, SVEC _initPower)
{
    _link  = _linkInfo;
    _power = _initPower;

    _R = DVEC(_link.size(), vector<double>(_link.size(), 0));
    _X = DVEC(_link.size(), vector<double>(_link.size(), 0));
}

//======================================================================
Network::~Network()
{
}

//======================================================================
vector<Node*> Network::getNodes() const
{
    return _nodes;
}

//======================================================================
void Network::buildNetwork()
{
    for (int i = 0; i < _link.size(); i++)
    {
        Node* _node = NULL;
        _node = new Node(Utility::strtoi(_link[i][1]));

        _node->setParentNode(Utility::strtoi(_link[i][0]));

        _R[_node->getId()][_node->getParentNode()] = Utility::strtod(_link[i][2]);
        _R[_node->getParentNode()][_node->getId()] = Utility::strtod(_link[i][2]);

        _X[_node->getId()][_node->getParentNode()] = Utility::strtod(_link[i][3]);
        _X[_node->getParentNode()][_node->getId()] = Utility::strtod(_link[i][3]);

        _nodes.push_back(_node);
    }

    for (int i = 0; i < _power.size(); i++)
    {
        if (Utility::strtod(_power[i][1]) != 0.0 || Utility::strtod(_power[i][2]) != 0.0)
        {
            for (int j = 0; j < _nodes.size(); j++)
            {
                if (_nodes[j]->getId() == Utility::strtoi(_power[i][0]))
                {
                    _nodes[j]->setActivePower( Utility::strtod(_power[i][1]));
                    _nodes[j]->setReactivePower(Utility::strtod(_power[i][2]));

                    _nodes[j]->setAmplitude(Utility::distance(_nodes[j]->getActivePower(), _nodes[j]->getReactivePower()));
                    _nodes[j]->setAngle(atan2(_nodes[j]->getActivePower(), _nodes[j]->getReactivePower()));
                    break;
                }
            }
        }
    }

    for (int i = 0; i < _link.size(); i++)
    {
        for (int j = 0; j < _link.size(); j++)
        {

        }
    }
}
