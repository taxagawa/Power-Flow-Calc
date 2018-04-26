#include "BFSCalc.h"
#include "FileIO.h"

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
    _fileIO->setDataPath(argc, argv);

    _fileIO->setInputs();
}

//======================================================================
