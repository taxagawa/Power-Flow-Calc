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
    using Utility::strtoi;
    using Utility::strtod;

    for (int i = 0; i < _link.size(), i++)
    {
        Node* _node = NULL;
        _node = new Node(strtoi(_link[i][1]));

        _node->_parentNode = strtoi(_link[i][0]);

        _R[_node->getID()][_node->_parentNode] = strtod(_link[i][2]);
        _R[_node->_parentNode][_node->getID()] = strtod(_link[i][2]);

        _X[_node->getID()][_node->_parentNode] = strtod(_link[i][3]);
        _X[_node->_parentNode][_node->getID()] = strtod(_link[i][3]);

        _nodes.push_back(_node);
    }

    for (int i = 0; i < _power.size(); i++)
    {
        if (strtod(_power[i][1]) != 0.0 || strtod(_power[i][2]) != 0.0)
        {
            for (int j = 0; j < _nodes.size(); j++)
            {
                if (_nodes[j]->getId() == strtoi(_power[i][0]))
                {
                    _nodes[j]->_activePower = strtod(_power[i][1]);
                    _nodes[j]->_reactivePower = strtod(_power[i][2]);

                    _node[j]->_amplitude = Utility::distance(_nodes[j]->_activePower, _nodes[j]->_reactivePower);
                    _node[j]->_angle = atan2((_nodes[j]->_activePower, _nodes[j]->_reactivePower));
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
