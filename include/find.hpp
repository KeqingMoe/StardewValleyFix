#pragma once
#include <regex>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <functional>
#include <iostream>

using namespace std;

const std::regex findreg(R"(^(?!SaveGameInfo)(?!.*(_old|\.vdf|\.bak)$).+$)");

inline bool is_regular_file(const std::string& path) {
    struct stat path_stat;
    stat(path.c_str(), &path_stat);
    return S_ISREG(path_stat.st_mode);
}

inline bool directory_exists(const string& path) {
    struct stat path_stat;
    if (stat(path.c_str(), &path_stat) != 0) return false;
    return S_ISDIR(path_stat.st_mode);
}

inline vector<string> find_in_directory(const string& dir_path) {
    vector<string> results;
    
    if (!directory_exists(dir_path)) {
        return results;
    }
    
    function<void(const string&)> traverse_directory = [&](const string& cur_path) {
        DIR* dir = opendir(cur_path.c_str());
        if (dir == nullptr) return;
        
        dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
                continue;
                
            string full_path = cur_path + "/" + entry->d_name;
            
            struct stat path_stat;
            stat(full_path.c_str(), &path_stat);
            if (S_ISDIR(path_stat.st_mode)) {
                traverse_directory(full_path);
            } else if (is_regular_file(full_path)) {
                string filename = entry->d_name;
                if (regex_match(filename, findreg)) {
                    results.push_back(full_path);
                }
            }
        }
        closedir(dir);
    };
    
    traverse_directory(dir_path);
    return results;
}

inline vector<string> find(const string& home_path) {
    // 检查多个可能的存档位置
    vector<string> possible_paths = {
        home_path + "/.config/StardewValley/Saves",  // macOS 位置
        home_path + "/AppData/Roaming/StardewValley/Saves"  // Windows 位置
    };
    
    vector<string> results;
    
    for (const auto& path : possible_paths) {
        cout << "正在检查路径: " << path << endl;
        auto path_results = find_in_directory(path);
        if (!path_results.empty()) {
            cout << "在 " << path << " 找到 " << path_results.size() << " 个存档文件" << endl;
            results.insert(results.end(), path_results.begin(), path_results.end());
        }
    }
    
    return results;
}