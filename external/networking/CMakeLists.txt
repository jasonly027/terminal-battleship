cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(battleship_networking
    VERSION 1.0
    LANGUAGES CXX
)



add_library(${PROJECT_NAME}
    src/server.cpp
)
if (NOT DEFINED ASIO_INCLUDE_DIR)
    message(FATAL_ERROR "Variable <ASIO_INCLUDE_DIR> is not defined. Please\
            define it by passing it as a CLI argument when running CMake.\
            Ex: -DASIO_INCLUDE_DIR:PATH=/path/to/asio/include/")
endif()
target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${ASIO_INCLUDE_DIR}
)



# Set using Asio without Boost
add_definitions(-DASIO_STANDALONE)
if (WIN32)
    # Set minimum Windows version for Windows SDK
    add_definitions(-D_WIN32_WINNT=0x0A00) # 0x0A00 = Win10
endif()