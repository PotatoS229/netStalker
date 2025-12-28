cmake_minimum_required(VERSION 3.10)
project(netStalker)

set(CMAKE_CXX_STANDARD 17)

# Основная программа
add_executable(netStalker 
    src/main.cpp
    src/network/configNetwork.cpp
    src/network/networkAttack.cpp
    src/network/networkInfo.cpp
    src/network/stressTest.cpp
    src/server/server.cpp
)

target_include_directories(netStalker 
    PRIVATE include
    PRIVATE include/network
    PRIVATE include/server
)