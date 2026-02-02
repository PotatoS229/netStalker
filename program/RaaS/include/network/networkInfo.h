#pragma once 
#include <string>
#include <vector> 
#include <iostream>
#include <iomanip>

namespace networkInfo{
    struct informate{
        std::vector<std::string> info{};
        void networkInfo();  
    };
}