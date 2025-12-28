#pragma once 
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

namespace configNetwork{
    struct configuration{
        std::vector<std::string> config;
        void configure();
    };
}