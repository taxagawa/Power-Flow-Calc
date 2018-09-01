#include "BFS.h"
#include "BFSCalc.h"
#include "FileIO.h"
#include "Utility.h"
#include <iostream>
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

    _linkInfo  = _fileIO->getLinkInfo();
    _initPower = _fileIO->getInitPower();

    BFS* _bfs = new BFS(_linkInfo, _initPower);
    _bfs->CalcLoop();

    outputAm     = _bfs->getOutputAm();
    outputTh     = _bfs->getOutputTh();
    finalStepNum = _bfs->getStepNum();

    _fileIO->receiveOutput(outputAm, outputTh, finalStepNum);
}
