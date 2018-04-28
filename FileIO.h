#ifndef __FILEIO_H__
#define __FILEIO_H__

#include <string>
#include <vector>

class FileIO
{
public:
    FileIO();

    //オプション解析
    bool setDataPath(int argc, char** argv);

    //パスを返す
    std::string getDataPath() const;

    //リンク情報をファイルから読み込む
    void readLinkInfo();

    //初期電力情報をファイルから読み込む
    void readInitPower();

    //リンク情報を返す
    std::vector< std::vector<std::string> > getLinkInfo() const;

    //初期電力情報を返す
    std::vector< std::vector<std::string> > getInitPower() const;

private:
    //パス
    std::string _dataPath;

    //リンク情報
    std::vector< std::vector<std::string> > _linkInfo;

    std::vector< std::vector<std::string> > _initPower;

private:
    //_dataPathにファイル名を追加
    std::string addPath(std::string file);
};

#endif //__FILEIO_H__
