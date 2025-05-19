#pragma once
#include <filesystem>
#include <fstream>
#include <iterator>
#include <regex>
#include <iostream>

using namespace std;


const std::regex fixreg(R"(<userID>\d*</userID>)");

inline void fix(const std::string& path)
{
    string bak_path = path + ".bak";
    
    ifstream src(path, ios::binary);
    ofstream dst(bak_path, ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    ifstream fin(bak_path);
    istreambuf_iterator<char> beg(fin), end;
    auto content = string{beg, end};
    fin.close();

    ofstream fout{path};
    ostream_iterator<char> it{fout};

    regex_replace(it,content.begin(),content.end(),fixreg,"<userID />");
    fout.close();
}