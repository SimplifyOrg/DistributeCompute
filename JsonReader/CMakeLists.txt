cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_BUILD_TYPE Debug)

target_sources(process PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/json_nlohmann_adapter.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/json_message_impl.cpp
            )
target_include_directories(process PUBLIC
                        ${CMAKE_CURRENT_SOURCE_DIR}
                        ${PROJECT_SOURCE_DIR})