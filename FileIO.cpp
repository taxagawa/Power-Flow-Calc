#include "FileIO.h"
#include "Utility.h"
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
bool FileIO::setData(int argc, char** argv)
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

    readLinkInfo();
    readInitPower();

    return true;
}

//====================================================================
void FileIO::readLinkInfo()
{
    ifstream inConnectFile(addPath("link.txt").c_str(), ios::in);
    if (!inConnectFile)
    {
        cerr << "Error: cannot find or open link file" << endl;
        exit(EXIT_FAILURE);
    }

    string str;
    while (getline(inConnectFile, str))
    {
        _linkInfo.push_back(split(str, ','))
    }
}

//====================================================================
void FileIO::readInitPower()
{
    ifstream inPowerfile(addPath("power.txt").c_str(), ios::in);
    if (!inPowerfile)
    {
        cerr << "Error: cannot find or open power file" << endl;
        exit(EXIT_FAILURE);
    }

    string str;
    while (getline(inPowerfile, str))
    {
        _initPower.push_back(split(str, ','))
    }
}

//====================================================================
SVEC FileIO::getLinkInfo() const
{
    return _linkInfo;
}

//====================================================================
SVEC FileIO::getInitPower() const
{
    return _initPower;
}

//====================================================================
string FileIO::addPath(string file)
{
    return _dataPath + file;
}
