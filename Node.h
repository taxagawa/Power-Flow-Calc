#ifndef __NODE_H__
#define __NODE_H__

#include <vector>

class Node
{
public:
    Node();

    //virtual ~Node();

    void setId(const int& id);

    int getID() const;

private:
    //ノード番号
    int _id;

    std::vector<int> _from;

    std::vector<int> _to;

    //有効電力
    double _activePower;

    //無効電力
    double _reactivePower;

};

#endif //__NODE_H__
