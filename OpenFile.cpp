#include <iostream>
#include <string>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main() {
    namespace fs = std::experimental::filesystem;
    std::string mypath { "../MyDir" };
    if(fs::exists(mypath))
    {

    }
}

