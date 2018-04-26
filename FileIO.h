#ifndef __FILEIO_H__
#define __FILEIO_H__

#include <string>

class FileIO
{
public:
    //オプション解析
    bool setDataPath(int argc, char** argv);

    //パスを返す
    std::string getDataPath() const;

    void setInputs();


private:
    //パス
    std::string _dataPath;

private:
    //_dataPathにファイル名を追加
    std::string addPath(std::string file);
};

#endif //__FILEIO_H__
