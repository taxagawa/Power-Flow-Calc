#ifndef __FILEIO_H__
#define __FILEIO_H__

#include <string>

class FileIO
{
protected:
    //オプション解析
    bool setDataPath(int argc, char** argv);

    //パスを返す
    std::string getDataPath() const;
private:
    //パス
    std::string _dataPath;
};

#endif //__FILEIO_H__
