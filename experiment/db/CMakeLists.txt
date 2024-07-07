cmake_minimum_required(VERSION 3.16...3.27)

# Setting the CMake policy version based on the current CMake version
if(CMAKE_VERSION VERSION_LESS 3.27)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.27)
endif()

project(Himmel VERSION 1.0
               DESCRIPTION "Himmel The Database"
               LANGUAGES CXX)

# FetchContent is used to download dependencies during the configure stage
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)

# Make Google Test available for use
FetchContent_MakeAvailable(googletest)

# Declare source files for the Himmel library
set(TASK_SOURCES
    src/main.cpp
    src/DB.cpp
    src/Tuple.cpp
    src/Table.cpp
)

# Add a shared library
add_library(himmel SHARED ${TASK_SOURCES})

# Include directories for the Himmel library
target_include_directories(himmel PUBLIC ${CMAKE_HOME_DIRECTORY}/include)

# Add the main executable
add_executable(${PROJECT_NAME} src/main.cpp) 

target_link_libraries(${PROJECT_NAME} PRIVATE himmel)

# Add executable for tests
# add_executable(basic_test tests/basic.cpp)

# Link Google Test to the test executable and the Himmel library
# target_link_libraries(basic_test PRIVATE gtest_main gtest himmel)

# Include Google Test's functionalities
include(GoogleTest)

# Enable CTest for running test cases
enable_testing()

# Discover tests added in the basic_test executable
# gtest_discover_tests(basic_test)