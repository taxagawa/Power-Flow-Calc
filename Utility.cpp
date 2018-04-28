#include "Utility.h"
#include <string>
#include <sstream>

using namespace std;

//======================================================================
double Utility::strtod(string src)
{
    double val;
    stringstream str;
    str << src;
    str >> val;
    return val;
}

//======================================================================
int Utility::strtoi(string src)
{
    int val;
    stringstream str;
    str << src;
    str >> val;
    return val;
}

//======================================================================
string Utility::itostr(int src)
{
    stringstream str;
    str << src;
    return str.str();
}

//======================================================================
string Utility::dtostr(double src)
{
    stringstream str;
    str << src;
    return str.str();
}
