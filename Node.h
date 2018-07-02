#ifndef __NODE_H__
#define __NODE_H__

#include <vector>

class Node
{
public:
    explicit Node(int id);

    //virtual ~Node();

    //getter & setter
    int getId() const;

    //parentNode
    void setParentNode(int parentNode);

    int getParentNode() const;

    //childNodes
    void setChildNodes(const int& id);

    std::vector<int> getChildNodes() const;

    //activePower
    void setActivePower(double activePower);

    double getActivePower() const;

    //dActivePower
    void setDefaultActivePower(double dActivePower);

    double getDefaultActivePower() const;

    //pActivePower
    void setPreActivePower(double pActivePower);

    double getPreActivePower() const;

    //reactivePower
    void setReactivePower(double reactivePower);

    double getReactivePower() const;

    //dReactivePower
    void setDefaultReactivePower(double dReactivePower);

    double getDefaultReactivePower() const;

    //pReactivePower
    void setPreReactivePower(double pReactivePower);

    double getPreReactivePower() const;

    //amplitude
    void setAmplitude(double amplitude);

    double getAmplitude() const;

    //preAmplitude
    void setPreAmplitude(double preAmplitude);

    double getPreAmplitude() const;

    //angle
    void setAngle(double angle);

    double getAngle() const;
    /*
    //比較演算子のオーバーロード
    bool operator<(const Node& right) const
    {
        return this->_id < right._id;
    }

    inline bool operator >=(const Node& node) const
    {
        return !(*this < node);
    }*/

protected:
    //ノード番号
    int _id;

    //親ノードのidを格納
    int _parentNode;

    //子ノードのidを格納
    std::vector<int> childNodes;

    //有効電力
    double _activePower;

    //デフォルトの有効電力
    double _dActivePower;

    //1step前の有効電力
    double _pActivePower;

    //無効電力
    double _reactivePower;

    //デフォルトの無効電力
    double _dReactivePower;

    //1step前の無効電力
    double _pReactivePower;

    //振幅
    double _amplitude;

    //k-1ステップ目の振幅
    double _preAmplitude;

    //位相
    double _angle;

};

#endif //__NODE_H__
