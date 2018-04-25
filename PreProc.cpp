#include "PreProc.h"
#include "FileIO.h"

using namespace std;

void PreProc::init(int argc, char** argv)
{
    FileIO->pathSetting(argc, argv);
}
