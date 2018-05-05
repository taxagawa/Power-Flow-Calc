#include "Network.h"
#include "Node.h"
#include "Utility.h"
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

//======================================================================
Network::Network(const SVEC& _linkInfo, const SVEC& _initPower)
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
void Network::buildNetwork()
{
    //Todo:計算量が多いので余裕があればパフォーマンスチューニング
    //それとメソッドかクラスに分ける

    //ノードの接続状況とインピーダンス行列の生成
    for (int i = 0; i < _link.size()-1; i++)
    {
        Node* _node = NULL;
        _node = new Node(Utility::strtoi(_link[i][1]));

        _node->setParentNode(Utility::strtoi(_link[i][0]));

        _R[_node->getId()][_node->getParentNode()] = Utility::strtod(_link[i][2]);
        _R[_node->getParentNode()][_node->getId()] = Utility::strtod(_link[i][2]);

        _X[_node->getId()][_node->getParentNode()] = Utility::strtod(_link[i][3]);
        _X[_node->getParentNode()][_node->getId()] = Utility::strtod(_link[i][3]);

        _nodes.push_back(_node);
        //debug
        cout << _node->gedId() << endl;
    }

    //初期の電力,振幅,位相の設定
    for (int i = 0; i < _power.size()-1; i++)
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

    //子ノードのvectorを生成 O(n^2)
    for (int i = 0; i < _link.size()-1; i++)
    {
        for (int j = 0; j < _link.size()-1; j++)
        {
            if (j == i)
            {
                continue;
            }
            else if (_nodes[j]->getParentNode() == _nodes[i]->getId())
            {
                _nodes[i]->getChildNodes().push_back(_nodes[j]->getId());
            }
        }
    }
}

//======================================================================
vector<Node*> Network::getNodes() const
{
    return _nodes;
}

//======================================================================
DVEC Network::getR() const
{
    return _R;
}

//======================================================================
DVEC Network::getX() const
{
    return _X;
}
