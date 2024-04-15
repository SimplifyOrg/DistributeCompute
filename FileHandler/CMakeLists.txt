cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_BUILD_TYPE Debug)

target_sources(process INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/file.cpp
            )

target_include_directories(process PUBLIC
                        ${CMAKE_CURRENT_SOURCE_DIR}
                        ${PROJECT_SOURCE_DIR})