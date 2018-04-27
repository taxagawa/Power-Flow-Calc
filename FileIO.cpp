#include "FileIO.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <getopt.h>

using namespace std;

//====================================================================
FileIO::FileIO(): _dataPath("./")
{
}

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
vector< vector<string> > FileIO::getConnections()
{
    ifstream inConnectFile(addPath("connection.txt").c_str(), ios::in);
    if (!inConnectFile)
    {
        cerr << "Error: cannot find or open connection file" << endl;
        exit(EXIT_FAILURE);
    }

    
}

//====================================================================
string FileIO::addPath(string file)
{
    return _dataPath + file;
}
