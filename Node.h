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

    void setActivePower(double activePower);

    double getActivePower() const;

    void setReactivePower(double reactivePower);

    double getReactivePower() const;

private:
    //ノード番号
    int _id;

    //idを格納
    std::vector<int> _from;

    //idを格納
    std::vector<int> _to;

    //有効電力
    double _activePower;

    //無効電力
    double _reactivePower;

};

#endif //__NODE_H__
