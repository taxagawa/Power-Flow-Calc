#include "FileIOManager.h"
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

//====================================================================
bool FileIOManager::setDataPath(int argc, char** argv)
{
    int opt;

    while((opt=getopt(argc, argv, "hd:")) != -1)
    {
        switch(opt)
        {
            case 'h':
                cout << " Usage: -d: input data directory." << endl;
                exit(0);
            case 'd':
                dataPath = optarg;
                if(!dataPath.empty())
                {
                    if (dataPath[dataPath.length()-1] != '/')
                    {
                        _path += '/';
                    }
                }
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }

    return true;
}

//====================================================================
string dataPath() const
{
    return dataPath;
}
