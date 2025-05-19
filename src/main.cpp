#include <homedir.hpp>
#include <find.hpp>
#include <fix.hpp>
#include <iostream>

using namespace std;

int main()
{
    string home_path = homedir();
    vector<string> saves = find(home_path);
    
    if (saves.empty()) {
        cout << "未找到Stardew Valley存档文件" << endl;
    } else {
        cout << "找到 " << saves.size() << " 个存档文件，正在修复..." << endl;
        for (const auto& save : saves) {
            cout << "修复文件: " << save << endl;
            fix(save);
        }
        cout << "修复完成!" << endl;
    }
    return 0;
}