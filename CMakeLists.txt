cmake_minimum_required(VERSION 3.20)

project(rgg)
set(CMAKE_CXX_STANDARD 11)
find_package(Boost 1.7 REQUIRED COMPONENTS)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(
            rgg
            app/main.cpp
            src/havel_hakimi.cpp
            src/pairing_model.cpp
            src/checker.cpp
            src/ioutils.cpp
            )
endif()
































































































