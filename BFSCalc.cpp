#include "BFSCalc.h"
#include "FileIO.h"
#include <string>

using namespace std;

//======================================================================
BFSCalc::BFSCalc()
{
    _fileIO = new FileIO();
}

//======================================================================
BFSCalc::~BFSCalc()
{
    if(_fileIO) delete _fileIO;
}

//======================================================================
void BFSCalc::dataSetting(int argc, char** argv)
{
    _fileIO->setData(argc, argv);

    _linkInfo  = _filiIO->getLinkInfo();
    _initPower = _fileIO->getInitPower();
}
