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

    //リンク情報をファイルから読み込む
    void readLinkInfo();

    //初期電力情報をファイルから読み込む
    void readInitPower();

    //リンク情報を返す
    SVEC getLinkInfo() const;

    //初期電力情報を返す
    SVEC getInitPower() const;

private:
    //パス
    std::string _dataPath;

    //リンク情報
    SVEC _linkInfo;

    //初期電力情報
    SVEC _initPower;

private:
    //_dataPathにファイル名を追加
    std::string addPath(std::string file);

    std::vector<std::string> split(const std::string &str, char delim);
};

#endif //__FILEIO_H__
