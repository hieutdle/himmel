cmake_minimum_required(VERSION 3.16...3.27)

if(${CMAKE_VERSION} VERSION_LESS 3.27)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.27)
endif()

project(Himmel VERSION 1.0
                  DESCRIPTION "Himmel The Database"
                  LANGUAGES CXX)
# Add an executable to the project using the specified source files
add_executable(Himmel
    src/Himmel.cpp
    src/Database.cpp
    src/Tuple.cpp
    src/Table.cpp
    # Add other source files here
)

target_include_directories(Himmel PUBLIC ${CMAKE_HOME_DIRECTORY}/include)