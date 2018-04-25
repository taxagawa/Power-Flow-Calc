#include <memory>
#include <cstdlib>
#include "PreProc.h"

using namespace std;

auto_ptr<PreProc> pProc;


//exit時に実行する関数
//pProcのデストラクタを明示的に呼び出す
void exitFunc()
{
    //resetはリソースの所有権を破棄し,新たなリソースの所有権を設定する関数
    pProc.reset();
}

int main(int argc, char* argv[])
{
    //プログラムが正常に終了するときに引数に指定した関数を呼び出す
    atexit(exitFunc);

    pProc.reset(new PreProc());
    pProc->init(argc, argv)

    exit(EXIT_SUCCESS);
}
