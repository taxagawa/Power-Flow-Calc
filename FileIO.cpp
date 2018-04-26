#include "FileIO.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <getopt.h>

using namespace std;

//====================================================================
bool FileIO::setDataPath(int argc, char** argv)
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
                _dataPath = optarg;
                if(!_dataPath.empty())
                {
                    if (_dataPath[_dataPath.length()-1] != '/')
                    {
                        _dataPath += '/';
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
string FileIO::getDataPath() const
{
    return _dataPath;
}

//====================================================================
