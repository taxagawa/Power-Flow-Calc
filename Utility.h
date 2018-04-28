#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <string>

//静的クラス

class Utility
{
public:
    //文字列をdoubleに変換
    static double strtod(std::string src);

    //文字列をintに変換
    static int strtoi(std::string src);

    //doubleを文字列に変換
    static std::string dtostr(double src);

    //intを文字列に変換
    static std::string itostr(int src);

private:
    Utility(){};
    ~Utility(){};
};

#endif //__UTILITY_H__
