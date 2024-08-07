cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_BUILD_TYPE Debug)
set(VCPKG_TARGET_TRIPLET x64-linux)
set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
project(ProcessManager VERSION 0.1.0 LANGUAGES C CXX)

find_package(rmqcpp REQUIRED)
find_package(bsl REQUIRED)
find_package(Boost REQUIRED COMPONENTS
    date_time filesystem iostreams)
find_package(spdlog CONFIG REQUIRED)
find_package(cpr REQUIRED)

add_library(process
        downloader.cpp
        config.cpp
        consumer_callback.cpp
        connection.cpp
        producer.cpp
        consumer.cpp
        action_process.cpp
        event.cpp
        event_loop.cpp
        )

add_executable(DistributeCompute main.cpp)

target_link_libraries(process PUBLIC 
    rmqcpp::rmq
    bsl
    boost_system
    Boost::filesystem
    spdlog::spdlog
    cpr::cpr
    )
add_subdirectory(unittests)
target_link_libraries(DistributeCompute PUBLIC 
        process
    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
