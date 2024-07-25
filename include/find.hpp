#pragma once
#include <filesystem>
#include <regex>
#include <string>
#include <vector>

using namespace std;

namespace fs=filesystem;

const std::regex findreg(R"(^(?!SaveGameInfo)(?!.*(_old|\.vdf|\.bak)$).+$)");

inline auto find(string home_path){
    auto path=format(R"({}\AppData\Roaming\StardewValley\Saves)",home_path);
    vector<fs::path> results;
    for (const fs::directory_entry& dir_entry :
            fs::recursive_directory_iterator(path))
    {
        if(!dir_entry.is_regular_file())continue;
        if(!regex_match(dir_entry.path().filename().string(),findreg))continue;
        results.emplace_back(dir_entry.path());
    }
    return results;
}