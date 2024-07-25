#pragma once
#include <filesystem>
#include <fstream>
#include <iterator>
#include <regex>

using namespace std;

namespace fs=filesystem;

const std::regex fixreg(R"(<userID>\d*</userID>)");

inline void fix(fs::path path)
{
    auto bak_path=format("{}.bak",path.string());
    fs::copy_file(path,bak_path,fs::copy_options::overwrite_existing);

    ifstream fin(bak_path);
    std::istreambuf_iterator<char> beg(fin), end;
    auto content=string{beg,end};

    ofstream fout{path};
    std::ostreambuf_iterator<char> it{fout};

    std::regex_replace(it,content.begin(),content.end(),fixreg,"<userID />");
}