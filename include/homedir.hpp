#pragma once
#include <cstdlib>
#include <string>

using namespace std;

inline string homedir()
{
    //return getenv("USERPROFILE");
    return getenv("HOME");
}