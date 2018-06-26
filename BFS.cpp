#include "BFS.h"
#include "Node.h"
#include "Utility.h"
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

using namespace std;

namespace
{
    const double EPS = 2.2943E-11;
}

//======================================================================
BFS::BFS(const vector<Node*>& nodes, const DVEC& R, const DVEC& X): _R(R), _X(X)
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
    vector<int> pNodeIdx;
    returnEndPoints(pNodeIdx, _nodes);
    //cout<< "a" << endl;
    //debug
    /*
    cout << "size: " << pNodeIdx.size() << endl;
    for (int i = 0; i < pNodeIdx.size(); i++)
    {
        cout << pNodeIdx[i] << endl;
    }
    */
    int step = 1;
    while (true)
    {
        cout << "Calculation Step: " << step << endl;
        step++;

        ForwardSweep(beginId);

        if (isConvergence() || step == 100)
        {
            break;
        }

        BackwardSweep(pNodeIdx);
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
            continue;
        }

        int parentNodeIdx = _nodes[id-1]->getParentNode()-1;
        complex<double> imag(0.0, 1.0);
        //forward計算
        double parentP = _nodes[parentNodeIdx]->getAmplitude() * cos(_nodes[parentNodeIdx]->getAngle());
        double parentQ = _nodes[parentNodeIdx]->getAmplitude() * sin(_nodes[parentNodeIdx]->getAngle());
        //親ノードの電圧（複素数）
        complex<double> parentV(parentP, parentQ);
        //cout << parentV << endl;
        //_Rと_Xだけはindexではなくidで管理
        complex<double> tmp1 = 1.0 - (((_nodes[parentNodeIdx]->getActivePower() * _R[id][parentNodeIdx+1])
                                + (_nodes[parentNodeIdx]->getReactivePower() * _X[id][parentNodeIdx+1])) / pow(parentV, 2.0));
        complex<double> tmp2 = ((_nodes[parentNodeIdx]->getReactivePower() * _R[id][parentNodeIdx+1])
                                - (_nodes[parentNodeIdx]->getActivePower() * _X[id][parentNodeIdx+1])) / pow(parentV, 2.0);

        complex<double> tmp3 = tmp1 + tmp2 * imag;
        //電圧（複素数）
        complex<double> vol = parentV * tmp3;

        _nodes[id-1]->setAmplitude(abs(vol));
        _nodes[id-1]->setAngle(arg(vol));
        //cout << "amp: " << _nodes[id-1]->getAmplitude() << " | theta: " << _nodes[id-1]->getAngle() << endl;
        }

}

//======================================================================
void BFS::BackwardSweep(vector<int> _pNodeIdx)
{
    vector<Node*> tmpNodes = _nodes;

    for (int i = 0; i < _pNodeIdx.size(); i++)
    {
        int index = _pNodeIdx[i];

        vector<int>::const_iterator itEnd = _nodes[index]->getChildNodes().end();
        for (vector<int>::const_iterator ite = _nodes[index]->getChildNodes().begin(); ite != itEnd; ite++)
        {
            int j = *ite - 1;
            _nodes[j]->setActivePower(_nodes[j]->getAmplitude() * cos(_nodes[j]->getAngle()));
            _nodes[j]->setReactivePower(_nodes[j]->getAmplitude() * sin(_nodes[j]->getAngle()));
        }
    }
    
    while (_pNodeIdx.size() != 0)
    {
        while (_pNodeIdx.size() != 0)
        {
            int index = _pNodeIdx[0];
            //cout << "id:" << index+1 << endl;
            //終了条件
            if (index == 125)
            {
                break;
            }
            //cout << _pNodeIdx.size() << endl;
            //先頭を削除すると要素の移動で無駄な計算時間が発生するので、reverseを用いることで計算量をO(1)に落とす
            reverse(_pNodeIdx.begin(), _pNodeIdx.end());
            _pNodeIdx.pop_back();
            //元に戻す
            reverse(_pNodeIdx.begin(), _pNodeIdx.end());

            //debug
            /*
            vector<int>::const_iterator itEnd12 = _pNodeIdx.end();
            for (vector<int>::const_iterator ite = _pNodeIdx.begin(); ite != itEnd12; ite++)
            {
                cout << *ite << endl;
            }
            */
            int step = 0;
            int size = _nodes[index]->getChildNodes().size();
            
            //double active   = 0.0;
            //double reactive = 0.0;
            complex<double> active(0.0, 0.0);
            complex<double> reactive(0.0, 0.0);
            //Backward計算
            vector<int>::const_iterator itEnd = _nodes[index]->getChildNodes().end();
            for (vector<int>::const_iterator ite = _nodes[index]->getChildNodes().begin(); ite != itEnd; ite++)
            {
                //cout << *ite << endl;
                step++;
                double P = _nodes[*ite-1]->getActivePower();
                double Q = _nodes[*ite-1]->getReactivePower();
                complex<double> V(P, Q);

                active   += P + ((_R[*ite][index+1] * (P * P + Q * Q)) / pow(V, 2));
                reactive += Q + ((_X[*ite][index+1] * (P * P + Q * Q)) / pow(V, 2));

                if (step == size)
                {
                    _nodes[index]->setActivePower(abs(active));
                    _nodes[index]->setReactivePower(abs(reactive));
                }
            }

            //cout << "a" << endl;
            tmpNodes[index]->getChildNodes().pop_back();
            //tmpNodes[index]->getChildNodes().shrink_to_fit();
            //debug
            /*
            vector<int>::const_iterator itEnd11 = tmpNodes[index]->getChildNodes().end();
            for (vector<int>::const_iterator ite = tmpNodes[index]->getChildNodes().begin(); ite != itEnd11; ite++)
            {
                cout << *ite << endl;
            }
            */
            //cout << "size: " << tmpNodes[index]->getChildNodes().size() << endl;;
        }
        
        returnEndPoints(_pNodeIdx, tmpNodes);
        cout << "b" << endl;
    }
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

//======================================================================
void BFS::returnEndPoints(vector<int>& tmpNodes, const vector<Node*> nodes)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if (hasChild(nodes[i]))
        {
            if (!(hasGrandchild(nodes[i])))
            {
                tmpNodes.push_back(nodes[i]->getId()-1);
                //cout << nodes[i]->getId()-1 << endl;
            }
        }
    }
}