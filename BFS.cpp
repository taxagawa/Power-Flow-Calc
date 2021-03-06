#include "BFS.h"
#include "Node.h"
#include "Utility.h"
#include <algorithm>
#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979
#endif

#define rad_to_deg(rad) (((rad)/M_PI)*180)

#define EPS 1.0E-8

//教訓：iteratorは無闇に使うべきではない

//======================================================================
BFS::BFS(const SVEC& _linkInfo, const SVEC& _initPower): step(1),limit(100)
{
    _link  = _linkInfo;
    _power = _initPower;

    _R = DVEC(_link.size(), vector<double>(_link.size(), 0));
    _X = DVEC(_link.size(), vector<double>(_link.size(), 0));

    outputAm = DVEC(_link.size(), vector<double>(limit+1, 0));
    outputTh = DVEC(_link.size(), vector<double>(limit+1, 0));
}

//======================================================================
void BFS::CalcLoop()
{
    buildNetwork();

    int beginId;
    //slack nodeの親ノードのidは0としておく(link.txt参照)
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

    for (int i = 0; i < _nodes.size(); i++)
    {
        outputAm[i+1][0] = (double)(i+1);
        outputTh[i+1][0] = (double)(i+1);
    }

    while (true)
    {
        cout << "*********************************************************" << endl;
        cout << "*    Calculation Step: " << step << endl;
        cout << "*********************************************************" << endl;

        setOutput();

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

        if (isConvergence() || step == limit)
        {
            for (int i = 0; i < _nodes.size(); i++)
            {
                outputAm[0][step+1] = (double)step;
                outputTh[0][step+1] = (double)step;

                outputAm[i+1][step+1] = _nodes[i]->getAmplitude();
                outputTh[i+1][step+1] = _nodes[i]->getAngle();
                //cout << "id: " << setfill('0') << setw(3) << right << i+1 << " | amp: " << setfill(' ') << setw(8) << left << _nodes[i]->getAmplitude() << " | theta: " << rad_to_deg(_nodes[i]->getAngle()) << endl;
            }
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

    while (id_vec.size() != 0)
    {
        int id = id_vec[0];
        //cout << "id:" << id << endl;
        //先頭を削除すると要素の移動で無駄な計算時間が発生する
        reverse(id_vec.begin(), id_vec.end());
        id_vec.pop_back();
        //元に戻す
        reverse(id_vec.begin(), id_vec.end());

        vector<int> child_vec = _nodes[id-1]->getChildNodes();
        int _size = child_vec.size();

        //番号がidのノードの子ノードベクトルをid_vecの末尾に接続
        if (_size != 0)
        {
            if (id_vec.size() != 0)
            {
                for (int i = 0; i < _size; i++)
                {
                    id_vec.push_back(child_vec[i]);
                }
            }
            else
            {
                id_vec = child_vec;
            }
        }

        //収束判定のために、前ステップにおける振幅の値を_preAmplitudeに保存
        _nodes[id-1]->setPreAmplitude(_nodes[id-1]->getAmplitude());

        //slack nodeは計算をしない
        if (id == 126)
        {
            _nodes[id-1]->setAmplitude(1.05);
            _nodes[id-1]->setAngle(0.0);

            //cout << "id: " << id << " | active: " << _nodes[id-1]->getActivePower() << " | reactive: " << _nodes[id-1]->getReactivePower() << endl;
            //cout << "id: " << id << " | amp: " << _nodes[id-1]->getAmplitude() << " | theta: " << rad_to_deg(_nodes[id-1]->getAngle()) << endl;
            continue;
        }
        //slack nodeの本来の位相角
        double base_angle = atan2(_nodes[beginId-1]->getReactivePower(), _nodes[beginId-1]->getActivePower());

        int parentNodeIdx = (_nodes[id-1]->getParentNode())-1;
        complex<double> imag(0.0, 1.0);
        //forward計算
        double parentP = _nodes[parentNodeIdx]->getActivePower();
        complex<double> parentQ(0.0, _nodes[parentNodeIdx]->getReactivePower());
        //親ノードの電圧
        double parentV = _nodes[parentNodeIdx]->getAmplitude();
        //cout << parentV << endl;
        complex<double> X(0.0, _X[id][parentNodeIdx+1]);
        //cout << "X:" << X << endl;
        //_Rと_Xはindexではなくidで管理
        complex<double> tmp1 = 1.0 - (((parentP * _R[id][parentNodeIdx+1]) + (parentQ * X)) / (parentV * parentV));
        //参照論文から式の符号を修正
        complex<double> tmp2 = (((parentQ * _R[id][parentNodeIdx+1]) + (parentP * X)) * imag) / (parentV * parentV);

        complex<double> tmp3 = tmp1 + tmp2;
        //cout << "tmp1:" << tmp1 << " tmp2:" << tmp2 << " tmp3:" << tmp3 << endl;
        //電圧
        double vol = parentV * tmp3.real();

        _nodes[id-1]->setAmplitude(vol);
        //slack nodeの位相角を0とするため、相対的に他のノードの角度をずらす必要がある（たぶん）
        _nodes[id-1]->setAngle(atan2(_nodes[id-1]->getReactivePower(), _nodes[id-1]->getActivePower()) - base_angle);
        //cout << "id: " << id << " | active: " << _nodes[id-1]->getActivePower() << " | reactive: " << _nodes[id-1]->getReactivePower() << endl;
        //cout << "id: " << id << " | amp: " << _nodes[id-1]->getAmplitude() << " | theta: " << rad_to_deg(_nodes[id-1]->getAngle()) << endl;
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

    stack<int> S;
    S.push(id);

    while (!S.empty())
    {
        int nid = S.top();

        //終了条件
        if (nid == 0)
        {
            break;
        }
        //cout << "***********     id:" << nid << "     ***********" << endl;

        //親ノードのID
        int parent = _nodes[nid-1]->getParentNode();

        vector<int> child_vec = _nodes[nid-1]->getChildNodes();
        int _size = child_vec.size();
        //cout << " parent:" << parent << endl;
        //まず端点かどうかをチェック
        if (!hasChild(_nodes[nid-1]))
        {
            _nodes[nid-1]->setPreActivePower(_nodes[nid-1]->getActivePower());
            _nodes[nid-1]->setPreReactivePower(_nodes[nid-1]->getReactivePower());
            visited[nid] = 1;
            S.pop();
            S.push(parent);
        }
        //次に子ノードがすべて訪問済みかどうかをチェック
        else if (!checkChildrenVisited(nid, visited))
        {
            for (int i = 0; i < _size; i++)
            {
                //訪問済みは飛ばす
                if (visited[child_vec[i]] == 1)
                {
                    continue;
                }

                S.push(child_vec[i]);
            }
        }
        //子ノードが全て訪問済みのノード
        else
        {
            _nodes[nid-1]->setPreActivePower(_nodes[nid-1]->getActivePower());
            _nodes[nid-1]->setPreReactivePower(_nodes[nid-1]->getReactivePower());
            //cout << "***********     id:" << nid << "     ***********" << endl;

            double active   = 0.0;
            double reactive = 0.0;

            for (int i = 0; i < _size; i++)
            {
                int tmp_idx = child_vec[i]-1;
                double P = _nodes[tmp_idx]->getPreActivePower();
                complex<double> Q(0.0, _nodes[tmp_idx]->getPreReactivePower());

                double R = _R[nid][tmp_idx+1];
                complex<double> X(0.0, _X[nid][tmp_idx+1]);

                double V;
                if (step == 1)
                {
                    V = 1.0;
                }
                else
                {
                    V = _nodes[tmp_idx]->getAmplitude();
                }
                //cout << "V:" << V << endl;
                complex<double> cActive(0.0, 0.0);
                cActive   = P + ((R * ((P * P) + (Q * Q))) / (V * V));

                active   += cActive.real();

                complex<double> cReactive(0.0, 0.0);
                cReactive = Q + ((X * ((P * P) + (Q * Q))) / (V * V));

                reactive += cReactive.imag();
                //cout << "P:" << P << " Q:" << Q << " R:" << R << " X:" << X << " tmp:" << tmp << " V:" << V << endl;
                //cout << "cActive:" << cActive << " cReactive:" << cReactive << endl;
                //cout << "active: " << active << " | reactive:" << reactive << endl;
            }
            //cout << "id:" << id << " active:" << active << " reactive:" << reactive << endl;

            _nodes[nid-1]->setActivePower(_nodes[nid-1]->getDefaultActivePower() + active);
            _nodes[nid-1]->setReactivePower(_nodes[nid-1]->getDefaultReactivePower() + reactive);

            //cout << "id:" << id << " DA:" << _nodes[nid-1]->getDefaultActivePower() << " DR:" << _nodes[nid-1]->getDefaultReactivePower() << endl;
            //_nodes[nid-1]->setPreActivePower(_nodes[nid-1]->getActivePower());
            //_nodes[nid-1]->setPreReactivePower(_nodes[nid-1]->getReactivePower());

            visited[nid] = 1;
            S.pop();
            S.push(parent);
        }
    }
}

//======================================================================
bool BFS::checkChildrenVisited(int id, int visited[])
{
    vector<int> v = _nodes[id-1]->getChildNodes();
    int _size = v.size();
    for (int i = 0; i < _size; i++)
    {
        if (visited[v[i]] == 0)
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
        if (abs( _nodes[i]->getAmplitude() - _nodes[i]->getPreAmplitude()) > EPS)
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
void BFS::setOutput()
{
    //ファイルの一行目
    outputAm[0][step] = (double)(step-1);
    outputTh[0][step] = (double)(step-1);

    for (int i = 0; i < _nodes.size(); i++)
    {
        outputAm[i+1][step] = _nodes[i]->getAmplitude();
        outputTh[i+1][step] = _nodes[i]->getAngle();
    }
}

//======================================================================
void BFS::buildNetwork()
{
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
        //cout << _node->getId() << endl;
        //cout << _node->getParentNode() << endl;
    }

    /*
    //一応idでソートしようとしたが、なぜか正しくソートされないので放置
    //第三引数にラムダ式を書いてもokらしいがコンパイルできるかわからんので一応演算子オーバーロードで

    sort(_nodes.begin(), _nodes.end());
    //debug
    for (int i = 0; i < _nodes.size(); i++)
    {
        cout << _nodes[i]->getId() << endl;
    }
    */
    //初期の電力,振幅,位相の設定
    for (int i = 0; i < _power.size()-1; i++)
    {
        if (Utility::strtod(_power[i][1]) != 0.0 || Utility::strtod(_power[i][2]) != 0.0)
        {
            for (int j = 0; j < _nodes.size(); j++)
            {
                if (_nodes[j]->getId() == Utility::strtoi(_power[i][0]))
                {
                    _nodes[j]->setActivePower(Utility::strtod(_power[i][1]));
                    _nodes[j]->setReactivePower(Utility::strtod(_power[i][2]));
                    _nodes[j]->setDefaultActivePower(Utility::strtod(_power[i][1]));
                    _nodes[j]->setDefaultReactivePower(Utility::strtod(_power[i][2]));

                    _nodes[j]->setAmplitude(Utility::distance(_nodes[j]->getActivePower(), _nodes[j]->getReactivePower()));
                    _nodes[j]->setAngle(atan2(_nodes[j]->getReactivePower(), _nodes[j]->getActivePower()));
                    break;
                }
            }
        }
    }
    /*
    for (int i = 0; i < _nodes.size(); i++)
    {
        cout << _nodes[i]->getActivePower() << endl;
    }
    */
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
                _nodes[i]->setChildNodes(_nodes[j]->getId());
            }
        }
    }
}

//======================================================================
vector<Node*> BFS::getNodes() const
{
    return _nodes;
}

//======================================================================
DVEC BFS::getR() const
{
    return _R;
}

//======================================================================
DVEC BFS::getX() const
{
    return _X;
}

//======================================================================
DVEC BFS::getOutputAm() const
{
    return outputAm;
}

//======================================================================
DVEC BFS::getOutputTh() const
{
    return outputTh;
}

//======================================================================
int BFS::getStepNum() const
{
    return step;
}

//======================================================================
//再帰が深すぎる
/*
void BFS::DFS(int id, int visited[])
{
    //cout << "***********     id:" << id << "     ***********" << endl;
    //終了条件
    if (id == 0)
    {
        return;
    }
    //親ノードのID
    int parent = _nodes[id-1]->getParentNode();
    if (parent == 0)
    {
        return;
    }

    //まず端点かどうかをチェック
    if (!hasChild(_nodes[id-1]))
    {
        //cout << "***********     id:" << id << "     ***********" << endl;
        _nodes[id-1]->setPreActivePower(_nodes[id-1]->getActivePower());
        _nodes[id-1]->setPreReactivePower(_nodes[id-1]->getReactivePower());
        visited[id] = 1;
        DFS(parent, visited);
    }
    //次に子ノードがすべて訪問済みかどうかをチェック
    else if (!checkChildrenVisited(id, visited))
    {
        vector<int>::const_iterator itEnd = _nodes[id-1]->getChildNodes().end();
        for (vector<int>::const_iterator ite =_nodes[id-1]->getChildNodes().begin(); ite != itEnd; ++ite)
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
        _nodes[id-1]->setPreActivePower(_nodes[id-1]->getActivePower());
        _nodes[id-1]->setPreReactivePower(_nodes[id-1]->getReactivePower());
        //cout << "***********     id:" << id << "     ***********" << endl;

        double active   = 0.0;
        double reactive = 0.0;
        complex<double> imaginary(0.0, 1.0);

        vector<int>::const_iterator itEnd = _nodes[id-1]->getChildNodes().end();
        for (vector<int>::const_iterator ite =_nodes[id-1]->getChildNodes().begin(); ite != itEnd; ++ite)
        {
            double P = _nodes[*ite-1]->getPreActivePower();
            complex<double> Q(0.0, _nodes[*ite-1]->getPreReactivePower());
            //double P = _nodes[*ite-1]->getActivePower();
            //complex<double> Q(0.0, _nodes[*ite-1]->getReactivePower());

            double R = _R[id][*ite];
            complex<double> X(0.0, _X[id][*ite]);

            double V;
            //cout << "step:" << step << endl;
            //complex<double> tmp = Q * imaginary;
            //double V = _nodes[*ite-1]->getAmplitude();
            if (step == 1)
            {
                V = 1.05;//Utility::distance(P, _nodes[*ite-1]->getReactivePower());
            }
            else
            {
                V = _nodes[*ite-1]->getAmplitude();
            }
            //cout << "V:" << V << endl;
            complex<double> cActive(0.0, 0.0);
            cActive   = P + ((R * ((P * P) + (Q * Q))) / (V * V));
            active   += cActive.real();

            complex<double> cReactive(0.0, 0.0);
            cReactive = Q + ((X * ((P * P) + (Q * Q))) / (V * V));

            reactive += cReactive.imag();
            //cout << "P:" << P << " Q:" << Q << " R:" << R << " X:" << X << " tmp:" << tmp << " V:" << V << endl;
            //cout << "cActive:" << cActive << " cReactive:" << cReactive << endl;
            //cout << "active: " << active << " | reactive:" << reactive << endl;
        }
        //cout << "id:" << id << " active:" << active << " reactive:" << reactive << endl;

        _nodes[id-1]->setActivePower(_nodes[id-1]->getDefaultActivePower() + active);
        _nodes[id-1]->setReactivePower(_nodes[id-1]->getDefaultReactivePower() + reactive);

        //_nodes[id-1]->setActivePower(active);
        //_nodes[id-1]->setReactivePower(reactive);

        //cout << "id:" << id << " DA:" << _nodes[id-1]->getDefaultActivePower() << " DR:" << _nodes[id-1]->getDefaultReactivePower() << endl;
        //_nodes[id-1]->setPreActivePower(_nodes[id-1]->getActivePower());
        //_nodes[id-1]->setPreReactivePower(_nodes[id-1]->getReactivePower());

        visited[id] = 1;
        DFS(parent, visited);
    }
}
*/
