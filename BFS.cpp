#include "BFS.h"
#include "Node.h"
#include "Utility.h"
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979
#endif

#define rad_to_deg(rad) (((rad)/M_PI)*180)

namespace
{
    const double EPS = 2.2943E-11;
}

//======================================================================
BFS::BFS(const vector<Node*>& nodes, const DVEC& R, const DVEC& X): _R(R), _X(X), step(1)
{
    _nodes = nodes;
}

//======================================================================
void BFS::CalcLoop()
{
    int beginId;
    int slackNodeParentId = 0;

    for (int i = _nodes.size()-1; i >= 0; i--)
    {
        //begin nodeが複数ある場合は修正が必要
        if (_nodes[i]->getParentNode() == slackNodeParentId)
        {
            beginId = i + 1;
            break;
        }
    }

    //子ノードを持つが孫ノードを持たないノードを格納
    //これらはBackward計算のスタートのノードとなる
    int endId;
    for (int i = 0; i < _nodes.size(); i++)
    {
        //適当に端点を一つ取得
        if (!hasChild(_nodes[i]))
        {
            endId = i + 1;
            break;
        }
    }

    _nodes[beginId-1]->setActivePower(0.5);
    _nodes[beginId-1]->setReactivePower(0.0);

    while (true)
    {
        cout << "*********************************************************" << endl;
        cout << "*Calculation Step: " << step << endl;
        cout << "*********************************************************" << endl;

        BackwardSweep(endId);
        /*
        for (int i = 0; i < _nodes.size(); i++)
        {
            cout << "id:" << _nodes[i]->getId();
            cout << " preA:" << _nodes[i]->getPreActivePower();
            cout << " A:" << _nodes[i]->getActivePower();
            cout << " preR:" << _nodes[i]->getPreReactivePower();
            cout << " R:" << _nodes[i]->getReactivePower() << endl;;
        }
        */
        ForwardSweep(beginId);

        if (isConvergence() || step == 100)
        {
            break;
        }

        step++;
    }
}

//======================================================================
void BFS::ForwardSweep(int beginId)
{
    vector<int> id_vec;
    id_vec.reserve(_nodes.size());

    id_vec.push_back(beginId);
    //cout << beginId << endl;

    while (id_vec.size() != 0)
    {
        int id = id_vec[0];
        //cout << "id:" << id << endl;
        //先頭を削除すると要素の移動で無駄な計算時間が発生するので、reverseを用いることで計算量をO(1)に落とす
        reverse(id_vec.begin(), id_vec.end());
        id_vec.pop_back();
        //元に戻す
        reverse(id_vec.begin(), id_vec.end());

        //debug
        /*
        //cout << "size:" << _nodes[id-1]->getChildNodes().size() << endl;
        vector<int>::iterator itEnd1 = _nodes[id-1]->getChildNodes().end();
        for (vector<int>::iterator ite = _nodes[id-1]->getChildNodes().begin(); ite != itEnd1; ite++)
        {
            cout << *ite << ",";
        }    
        cout << endl;
        */
        //番号がidのノードの子ノードベクトルをid_vecの末尾に接続
        //cout << id -1 << endl;
        //cout << _nodes[id-1]->getId() << endl;
        if (_nodes[id-1]->getChildNodes().size() != 0)
        {
            if (id_vec.size() != 0)
            {
                vector<int>::iterator itEnd = _nodes[id-1]->getChildNodes().end();
                for (vector<int>::iterator ite = _nodes[id-1]->getChildNodes().begin(); ite != itEnd; ite++)
                {
                    //cout << *ite << ",";
                    id_vec.push_back(*ite);
                }    
                //ベクトルの連結をググると以下の二つが推奨されているが、実際はメモリ周りのバグが発生してしまった　なぜ
                //id_vec.insert(id_vec.end(), _nodes[id-1]->getChildNodes().begin(), _nodes[id-1]->getChildNodes().end());
                //copy(_nodes[id-1]->getChildNodes().begin(), _nodes[id-1]->getChildNodes().end(), back_inserter(id_vec));
            }
            else
            {
                id_vec = _nodes[id-1]->getChildNodes();
            }
        }

        //debug
        /*
        vector<int>::iterator itEnd2 = id_vec.end();
        for (vector<int>::iterator ite = id_vec.begin(); ite != itEnd2; ite++)
        {
            cout << *ite << ",";
        }
        cout << endl;
        */
        //収束判定のために、前ステップにおける振幅の値を_preAmplitudeに保存
        _nodes[id-1]->setPreAmplitude(_nodes[id-1]->getAmplitude());

        //slack nodeはforward計算をしない
        if (id == 126)
        {
            _nodes[id-1]->setAmplitude(1.05);
            _nodes[id-1]->setAngle(0.0);

            _nodes[id-1]->setActivePower(_nodes[id-1]->getAmplitude() * cos(_nodes[id-1]->getAngle()));
            _nodes[id-1]->setReactivePower(_nodes[id-1]->getAmplitude() * sin(_nodes[id-1]->getAngle()));
            //cout << "active:" << _nodes[id-1]->getActivePower() << " reactive:" << _nodes[id-1]->getReactivePower() << endl; 
            cout << "id: " << id << " | amp: " << _nodes[id-1]->getAmplitude() << " | theta: " << rad_to_deg(_nodes[id-1]->getAngle()) << endl; 
            continue;
        }

        int parentNodeIdx = (_nodes[id-1]->getParentNode())-1;
        complex<double> imag(0.0, 1.0);
        //forward計算
        //double parentP = _nodes[parentNodeIdx]->getAmplitude() * cos(_nodes[parentNodeIdx]->getAngle());
        //complex<double> parentQ(0.0, _nodes[parentNodeIdx]->getAmplitude() * sin(_nodes[parentNodeIdx]->getAngle()));
        double parentP = _nodes[parentNodeIdx]->getActivePower();
        complex<double> parentQ(0.0, _nodes[parentNodeIdx]->getReactivePower());
        //親ノードの電圧
        //complex<double> tmp0 = parentQ * imag; 
        double parentV = _nodes[parentNodeIdx]->getAmplitude();
        //cout << parentV << endl;
        complex<double> X(0.0, _X[id][parentNodeIdx+1]);
        //_Rと_Xはindexではなくidで管理
        complex<double> tmp1 = 1.0 - (((parentP * _R[id][parentNodeIdx+1])
                                + (parentQ * X)) / (parentV * parentV));
        complex<double> tmp2 = (((parentQ * _R[id][parentNodeIdx+1])
                                - (parentP * X)) * imag) / (parentV * parentV);

        complex<double> tmp3 = tmp1 + tmp2;
        //電圧
        double vol = parentV * tmp3.real();

        _nodes[id-1]->setAmplitude(vol);
        _nodes[id-1]->setAngle(atan2(_nodes[id-1]->getReactivePower(), _nodes[id-1]->getActivePower()));
        cout << "id: " << id << " | amp: " << _nodes[id-1]->getAmplitude() << " | theta: " << rad_to_deg(_nodes[id-1]->getAngle()) << endl;        
        }
}

//======================================================================
void BFS::BackwardSweep(int id)
{
    //探索済みノードを判別するための配列
    //0が未探索で、1が探索済み
    //idで管理
    int visited[_nodes.size()+1];
    for (int i = 0; i < _nodes.size()+1; i++)
    {
        visited[i] = 0;
    }
    //必要あるかわからないけどコピーする
    int endId = id;

    DFS(endId, visited);
}

//======================================================================
void BFS::DFS(int id, int visited[])
{
    //cout << "***********     id:" << id << "     ***********" << endl;
    //親ノードのID
    int parent = _nodes[id-1]->getParentNode();
    //終了条件
    if (id == 0)
    {
        return;
    }

    //まず端点かどうかをチェック
    if (!hasChild(_nodes[id-1]))
    {
        //_nodes[id-1]->setPreActivePower(_nodes[id-1]->getActivePower());
        //_nodes[id-1]->setPreReactivePower(_nodes[id-1]->getReactivePower());
        visited[id] = 1;
        DFS(parent, visited);
    }
    //次に子ノードがすべて訪問済みかどうかをチェック
    else if (!checkChildrenVisited(id, visited))
    {
        vector<int>::const_iterator itEnd = _nodes[id-1]->getChildNodes().end();
        for (vector<int>::const_iterator ite =_nodes[id-1]->getChildNodes().begin(); ite != itEnd; ite++)
        {
            if (visited[*ite] == 1)
            {
                continue;
            }

            DFS(*ite, visited);
        }
    }
    //それ以外
    else
    {
        //_nodes[id-1]->setPreActivePower(_nodes[id-1]->getActivePower());
        //_nodes[id-1]->setPreReactivePower(_nodes[id-1]->getReactivePower());

        double active   = 0.0;
        double reactive = 0.0;
        complex<double> imag(0.0, 1.0);

        vector<int>::const_iterator itEnd = _nodes[id-1]->getChildNodes().end();
        for (vector<int>::const_iterator ite =_nodes[id-1]->getChildNodes().begin(); ite != itEnd; ite++)
        {
            double P = _nodes[*ite-1]->getActivePower();
            complex<double> Q(0.0, _nodes[*ite-1]->getReactivePower());

            double R = _R[id][*ite];
            complex<double> X(0.0, _X[id][*ite]);

            double V;
            //complex<double> tmp = Q * imag;
            //double V = _nodes[*ite-1]->getAmplitude();
            if (step == 1)
            {
                V = Utility::distance(P, _nodes[*ite-1]->getReactivePower());
            }
            else
            {
                V = _nodes[*ite-1]->getAmplitude();
            }
            
            complex<double> cActive(0.0, 0.0);
            cActive   = P + ((R * ((P * P) + (Q * Q))) / (V * V));
            active   += cActive.real();

            complex<double> cReactive(0.0, 0.0); 
            cReactive = Q + ((X * ((P * P) + (Q * Q))) / (V * V));

            reactive += cReactive.imag(); 
            //cout << "P:" << P << " Q:" << Q << " R:" << R << " X:" << X << " tmp:" << tmp << " V:" << V << endl;
            //cout << "cActive:" << cActive << " cReactive:" << cReactive << endl;
        }
        //cout << "id:" << id << " active:" << active << " reactive:" << reactive << endl;

        _nodes[id-1]->setActivePower(active);
        _nodes[id-1]->setReactivePower(reactive);

        //_nodes[id-1]->setPreActivePower(_nodes[id-1]->getActivePower());
        //_nodes[id-1]->setPreReactivePower(_nodes[id-1]->getReactivePower());

        visited[id] = 1;
        DFS(parent, visited);

        //次はstep数でVの値をわける
    }
}

//======================================================================
bool BFS::checkChildrenVisited(int id, int visited[])
{
    vector<int>::const_iterator itEnd = _nodes[id-1]->getChildNodes().end();
    for (vector<int>::const_iterator ite =_nodes[id-1]->getChildNodes().begin(); ite != itEnd; ite++)
    {
        if (visited[*ite] == 0)
        {
            return false;
        }
    }

    return true;
}

//======================================================================
bool BFS::isConvergence()
{
    for (int i = 0; i < _nodes.size(); i++)
    {
        if (abs(_nodes[i]->getPreAmplitude() - _nodes[i]->getAmplitude()) > EPS)
        {
            return false;
        }
    }

    return true;
}

//======================================================================
bool BFS::hasChild(const Node* node) const
{
    if (node->getChildNodes().size() == 0)
    {
        return false;
    }
    return true;
}

//======================================================================
/*
bool BFS::hasGrandchild(const Node* node) const
{
    //debug
    //cout << node->getId() << ":";

    int p = 0;
    int q = node->getChildNodes().size();
    //cout << "q:" << q << " ";

    //子ノードを持つ前提で使用
    vector<int>::const_iterator itEnd = node->getChildNodes().end();

    for (vector<int>::const_iterator ite = node->getChildNodes().begin(); ite != itEnd; ++ite)
    {
        //cout << *ite << ",";
        if (!(hasChild(_nodes[*ite-1])))
        {
            p++;
        }
    }

    //cout << " p:" << p << endl;
    if (p == q)
    {
        return false;
    } 
    else 
    {
        return true;
    }
}
*/