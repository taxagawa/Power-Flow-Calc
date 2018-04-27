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

    //接続状況をファイルから取得して返す
    std::vector< std::vector<std::string> > getConnections();


private:
    //パス
    std::string _dataPath;

private:
    //_dataPathにファイル名を追加
    std::string addPath(std::string file);
};

#endif //__FILEIO_H__
