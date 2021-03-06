#ifndef __FILEIO_H__
#define __FILEIO_H__

#include "Utility.h"
#include <string>
#include <vector>

class FileIO
{
public:
    FileIO();

    //オプション解析+データセッティング
    bool setData(int argc, char** argv);

    //リンク情報を返す
    SVEC getLinkInfo() const;

    //初期電力情報を返す
    SVEC getInitPower() const;

    //結果ファイル受け取り
    void receiveOutput(const DVEC& outputAM, const DVEC& outputTh, int num);

private:
    //パス
    std::string _dataPath;

    //リンク情報
    SVEC _linkInfo;

    //初期電力情報
    SVEC _initPower;

    //振幅の厳密解
    std::vector<std::string> _A;

    //位相の厳密解
    std::vector<std::string> _angle;

    DVEC _outputAm;

    DVEC _outputTh;

private:
    //リンク情報をファイルから読み込む
    void readLinkInfo();

    //初期電力情報をファイルから読み込む
    void readInitPower();

    //振幅の厳密解を読み込む
    void readAmplitude();

    //位相の厳密解を読み込む
    void readAngle();

    //_dataPathにファイル名を追加
    std::string addPath(std::string file);

    std::vector<std::string> split(const std::string &str, char delim);

    //結果ファイル生成
    void outputFactory(DVEC output, int num, std::string fileName, std::vector<std::string> solution);
};

#endif //__FILEIO_H__
