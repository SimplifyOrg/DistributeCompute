cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_BUILD_TYPE Debug)

include(CTest)
enable_testing()

add_executable(
            test_event_loop  
            test_event_loop.cpp
            )

target_link_libraries(test_event_loop PUBLIC 
            process
        )