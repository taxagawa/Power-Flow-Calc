#include "BFSCalc.h"
#include "FileIO.h"
#include "Network.h"
#include "Utility.h"
#include <string>

using namespace std;

//======================================================================
BFSCalc::BFSCalc()
{
    //オブジェクトをメンバ変数にするのと、一時オブジェクトとして使うことの違いは？
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

    _linkInfo  = _fileIO->getLinkInfo();
    _initPower = _fileIO->getInitPower();

    Network* _network = new Network(_linkInfo, _initPower);
    _network->buildNetwork();
}
