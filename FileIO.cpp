#include "FileIO.h"
#include "Utility.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
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
        _linkInfo.push_back(split(str, ','));
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
        _initPower.push_back(split(str, ','));
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

//====================================================================
vector<string> FileIO::split(const string &str, char delim){
    istringstream iss(str);
    string tmp;
    vector<string> res;
    while(getline(iss, tmp, delim))
    {
        res.push_back(tmp);
    }
    return res;
}

//====================================================================
void FileIO::receiveOutput(const DVEC& outputAm, const DVEC& outputTh, int num)
{
    _outputAm = outputAm;
    _outputTh = outputTh;

    outputFactory(_outputAm, num, addPath("outputAm.txt").c_str());
    outputFactory(_outputTh, num, addPath("outputTh.txt").c_str());
}

//====================================================================
void FileIO::outputFactory(DVEC output, int num, string fileName)
{
    ofstream outFile(fileName.c_str(), ios::out);
    if (!outFile.fail())
    {
        for (int i = 0; i < output.size(); i++)
        {
            for (int j = 0; j < num + 1; j++)
            {
                //先頭に'#'を挿入
                if (i == 0 && j == 0)
                {
                    outFile << "#" << " ";
                    continue;
                }

                outFile << Utility::dtostr(output[i][j]) << " ";
            }
            outFile << Utility::dtostr(output[i][num+1]) << endl;
        }
        outFile.close();
    }
}
