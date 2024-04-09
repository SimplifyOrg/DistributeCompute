# Distribute Compute

#### Init Cmake:

> cmake -DCMAKE_BUILD_TYPE=Debug -S /path/to/processManager -B /path/to/processManager/build

#### Build:

> cmake --build /path/to/processManager/build

## How to unit tests:

In unittest/CMakeLists.txt
- Add following lines:

            add_executable(
                unit_test
                unit_test.cpp
            )

            target_link_libraries(unit_test PUBLIC
                process
                bsl
                boost_system
                Boost::filesystem
                ... # Add other dependencies
            )

            add_test(unit_test unit_test)

- Run unit test as follows:

    ```cmd
    > $ ctest
    ```

    For verbose output
    ```cmd
    > $ ctest --verbose
    ```

    Log file will be generated when a test fails. So try to add as many logging information as needed.

## How to setup pre-commit hook run on local machine:

Pre commit hooks are some pre existing hooks which can be reused for common validation at the time of commit.

Precommit needs to be setup on local machine to be able to commit.

- Install Python version >= 3.10
- Install pre-commit
    ```cmd
    > $ pip install pre-commit
    > $ pre-commit install
    ```

Once pre-commit is setup some basic validation will run at the time of commit and push.
Pre-commit can also be run manually as follows:

    ```cmd
    > $ pre-commit run --all-files
    ```