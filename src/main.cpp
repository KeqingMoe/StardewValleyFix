#include <homedir.hpp>
#include <find.hpp>
#include <fix.hpp>

using namespace std;

int main()
{
    auto home_path=homedir();
    auto saves=find(home_path);
    for(auto&& save:saves){
        fix(save);
    }
}