#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "Node.h"
#include "Utility.h"
#include <string>
#include <vector>

class Network
{
public:
    Network(SVEC _linkInfo, SVEC _initPower);

    ~Network();

    //ノード・インピーダンスの設定
    void buildNetwork();

    //getter
    std::vector<Node*> getNodes() const;

    DVEC getR() const;

    DVEC getX() const;

private:
    SVEC _link;

    SVEC _power;

    //ノードの集合
    std::vector<Node*> _nodes;

    //レジスタンス行列
    DVEC _R;

    //リアクタンス行列
    DVEC _X;

};

#endif //__NETWORK_H__
