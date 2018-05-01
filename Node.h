#ifndef __NODE_H__
#define __NODE_H__

#include <vector>

class Node
{
public:
    explicit Node(int id);

    //virtual ~Node();

    void setId(const int& id);

    int getID() const;

    void setActivePower(double activePower);

    double getActivePower() const;

    void setReactivePower(double reactivePower);

    double getReactivePower() const;

private:
    //ノード番号
    int _id;

    //親ノードのidを格納
    int _parentNode;

    //子ノードのidを格納
    std::vector<int> _childNodes;

    //有効電力
    double _activePower;

    //無効電力
    double _reactivePower;

    //振幅
    double _amplitude;

    //位相
    double _angle;

};

#endif //__NODE_H__
