#include "FileIO.h"
#include "FileIOManager.h"

using namespace std;

bool FileIO::pathSetting(int argc, char** argv)
{
    fileIOm->setDataPath(argc, argv);
}
