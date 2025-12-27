cmake_minimum_required(VERSION 3.15)
project(netstalker VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Предупреждения
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Исходные файлы
add_executable(netstalker
    src/netStalker.cpp
    src/network/configNetwork.cpp
    src/network/networkAtack.cpp
    src/network/networkInfo.cpp
    src/network/stressTest.cpp
)

# Заголовочные файлы
target_include_directories(netstalker
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Тесты (если есть)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()