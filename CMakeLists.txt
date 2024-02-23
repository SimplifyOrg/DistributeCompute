cmake_minimum_required(VERSION 3.5.0)
set(VCPKG_ROOT /home/abs/vcpkg/vcpkg)
set(VCPKG_TARGET_TRIPLET x64-linux)
set(CMAKE_TOOLCHAIN_FILE /home/abs/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)
include(/home/abs/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(ProcessManager VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()
find_package(rmqcpp REQUIRED)
find_package(bsl REQUIRED)
find_package(Boost REQUIRED)

add_executable(ProcessManager 
        config.cpp
        connection.cpp
        producer.cpp
        consumer.cpp
        main.cpp
        )
target_link_libraries(ProcessManager PUBLIC 
    rmqcpp::rmq
    bsl
    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
