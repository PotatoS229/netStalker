cmake_minimum_required(VERSION 3.15)
project(netStalker
    VERSION 1.0.0
    DESCRIPTION "Network analysis and security tool"
    LANGUAGES CXX
)

# Настройка стандарта C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Политики CMake
cmake_policy(SET CMP0077 NEW)

# Опции конфигурации
option(BUILD_TESTS "Build tests" ON)
option(BUILD_WEB_GUI "Build with web GUI support" ON)
option(BUILD_AS_LIBRARY "Build as library" OFF)
option(ENABLE_DEBUG "Enable debug mode" OFF)

# Флаги компиляции
if(ENABLE_DEBUG)
    add_compile_definitions(DEBUG_MODE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

# Предупреждения
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
    if(ENABLE_DEBUG)
        add_compile_options(-fsanitize=address,undefined)
    endif()
elseif(MSVC)
    add_compile_options(/W4)
endif()

# Поиск зависимостей
find_package(Threads REQUIRED)

# Проверка необходимых файлов
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    message(FATAL_ERROR "main.cpp not found in src/ directory. Please create it.")
endif()

# Если нужна веб-часть
if(BUILD_WEB_GUI)
    find_package(PkgConfig)
    pkg_check_modules(LIBMICROHTTPD libmicrohttpd)
    if(LIBMICROHTTPD_FOUND)
        message(STATUS "Found libmicrohttpd: ${LIBMICROHTTPD_VERSION}")
    else()
        message(WARNING "libmicrohttpd not found, web GUI will be disabled")
        set(BUILD_WEB_GUI OFF)
    endif()
endif()

# Создание основной библиотеки с проверкой файлов
set(NETSTALKER_SOURCES "")

# Проверяем и добавляем файлы по одному
function(check_and_add_files pattern variable)
    file(GLOB_RECURSE FOUND_FILES ${pattern})
    if(FOUND_FILES)
        list(APPEND ${variable} ${FOUND_FILES})
        set(${variable} ${${variable}} PARENT_SCOPE)
        message(STATUS "Found files for ${pattern}: ${FOUND_FILES}")
    else()
        message(WARNING "No files found matching pattern: ${pattern}")
    endif()
endfunction()

# Поиск исходных файлов
check_and_add_files("${CMAKE_CURRENT_SOURCE_DIR}/src/network/*.cpp" NETSTALKER_SOURCES)
check_and_add_files("${CMAKE_CURRENT_SOURCE_DIR}/src/server/*.cpp" NETSTALKER_SOURCES)
check_and_add_files("${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" NETSTALKER_SOURCES)

# Если нет исходных файлов для библиотеки, создаем минимальную
if(NOT NETSTALKER_SOURCES)
    message(STATUS "No library source files found. Creating minimal library.")
    # Создаем заглушку
    set(DUMMY_LIB_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/dummy_lib.cpp")
    file(WRITE ${DUMMY_LIB_SOURCE} 
        "void netStalker_dummy_function() {}\n"
        "// Minimal library implementation\n"
    )
    set(NETSTALKER_SOURCES ${DUMMY_LIB_SOURCE})
endif()

# Создаем библиотеку
add_library(netStalker_lib STATIC ${NETSTALKER_SOURCES})

# Директории include
target_include_directories(netStalker_lib 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Связываем зависимости
target_link_libraries(netStalker_lib
    PUBLIC
        Threads::Threads
)

if(BUILD_WEB_GUI AND LIBMICROHTTPD_FOUND)
    target_include_directories(netStalker_lib
        PUBLIC ${LIBMICROHTTPD_INCLUDE_DIRS}
    )
    target_link_libraries(netStalker_lib
        PUBLIC ${LIBMICROHTTPD_LIBRARIES}
    )
    target_compile_definitions(netStalker_lib
        PUBLIC WITH_WEB_GUI
    )
endif()

# Опция сборки как библиотека
if(BUILD_AS_LIBRARY)
    install(TARGETS netStalker_lib
        EXPORT netStalkerTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h"
    )
    
    install(EXPORT netStalkerTargets
        FILE netStalkerConfig.cmake
        NAMESPACE netStalker::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/netStalker
    )
    
    message(STATUS "Building netStalker as library")
    return()
endif()

# Главное приложение
add_executable(netStalker ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_include_directories(netStalker
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(netStalker
    PRIVATE netStalker_lib
)

# Установка приложения
install(TARGETS netStalker
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Сводка
message(STATUS "")
message(STATUS "========================================")
message(STATUS "  netStalker Configuration Summary")
message(STATUS "========================================")
message(STATUS "  Version:        ${PROJECT_VERSION}")
message(STATUS "  Source files:   ${NETSTALKER_SOURCES}")
message(STATUS "  Main executable: ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
message(STATUS "========================================")