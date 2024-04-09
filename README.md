# Distribute Compute

#### Init Cmake:

> cmake -DCMAKE_BUILD_TYPE=Debug -S /path/to/processManager -B /path/to/processManager/build

#### Build:

> cmake --build /path/to/processManager/build

## How to add unit tests:

In unittest/CMakeLists.txt
- Add following lines
        
            add_executable(
                unit_test 
                unit_test.cpp
            )
            
            target_link_libraries(unit_test PUBLIC 
                process
                bsl
                boost_system
                Boost::filesystem
                boost_system
                ...
            )

            add_test(unit_test unit_test)

