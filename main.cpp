#include <memory>
#include <cstdlib>
#include "BFSCalc.h"

using namespace std;

auto_ptr<BFSCalc> bfsC;

int main(int argc, char* argv[])
{
    bfsC.reset(new BFSCalc());
    bfsC->dataSetting(argc, argv);

    exit(EXIT_SUCCESS);
}
