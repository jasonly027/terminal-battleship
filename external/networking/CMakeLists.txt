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
# [[EDIT THIS FOR YOUR CASE]]
# Specify include directory of Asio
set(PATH_TO_ASIO "C://Users//yoish//git//cpp//sdks//asio-1.28.0//include")
target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${PATH_TO_ASIO}
)



# Set using Asio without Boost
add_definitions(-DASIO_STANDALONE)
# Set minimum Windows version for Windows SDK
add_definitions(-D_WIN32_WINNT=0x0A00) # 0x0A00 = Win10