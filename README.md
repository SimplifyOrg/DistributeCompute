# Distribute Compute

## Build: Linux Debian

### Prerequisites for Linux:
> - GIT version >= 2.34.1
> - Cmake version >= 3.5.0
> - G++ version >= 11.4.0

### Build using VCPKG (Recommended)

- Install VCPKG based on instruction from [offical page](https://github.com/microsoft/vcpkg?tab=readme-ov-file#quick-start-unix).
- Set VCPKG_ROOT environment variable to point to vcpkg install directory.
  ``` cmd
  > $ export VCPKG_ROOT=/path/to/vcpkg_install_dir
  ```
  
- Install below VCPKG package:
  
  Needed for connecting with rabbitMQ. RMQCPP runs it's own event loop when consuming messages.
  ```cmd
  > $ ./vcpkg install rmqcpp
  ```

  Needed for thread management and file handling.
  ``` cmd
  > $ ./vcpkg install Boost
  ```

  Needed for REST endpoint call. Currently using it for downloading files.
  ```cmd
  > $ ./vcpkg install cpr
  ```

  Needed for logging.
  ```cmd
  > $ ./vcpkg install spdlog
  ```

- Git clone the DistributeCompute project on your local machine.
  ``` cmd
  > $ git clone https://github.com/SimplifyOrg/DistributeCompute.git
  ```

- Project is currently using [Nlohmann JSON framework](https://github.com/nlohmann/json) for JSON file parsing.
- Build as using following commands
  
  #### Init Cmake:

  ```cmd
  > $ cmake -DCMAKE_BUILD_TYPE=Debug -S /path/to/processManager -B /path/to/processManager/build
  ```
  
  #### Build:

  ```cmd
  > $ cmake --build /path/to/processManager/build
  ```
  
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
