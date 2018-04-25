#ifndef __FILEIOMANAGER_H__
#define __FILEIOMANAGER_H__

#include <string>

class FileIOManager
{
protected:
    //オプション解析
    bool setDataPath(int argc, char** argv);

    //パスを返す
    std::string dataPath() const;
private:
    //パス
    std::string dataPath;
};

#endif //__FILEIOMANAGER_H__
