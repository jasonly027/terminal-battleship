cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(battleship
    VERSION 1.0
    LANGUAGES CXX
)

if (NOT DEFINED ASIO_INCLUDE_DIR)
    message(FATAL_ERROR "Variable <ASIO_INCLUDE_DIR> is not defined. Please\
            define it by passing it as a CLI argument when running CMake.\
            Ex: -DASIO_INCLUDE_DIR:PATH=/path/to/asio/include/")
endif()
set(BATTLESHIP_NETWORKING_DIR "${CMAKE_SOURCE_DIR}/external/networking")



add_executable(${PROJECT_NAME})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${ASIO_INCLUDE_DIR}
    ${BATTLESHIP_NETWORKING_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/networking
)



# For testing purposes only
add_executable(Client
    src/client.cpp
)
target_include_directories(Client
    PRIVATE
    ${ASIO_INCLUDE_DIR}
    ${BATTLESHIP_NETWORKING_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_executable(Server
    src/server.cpp
)
target_include_directories(Server
    PRIVATE
    ${ASIO_INCLUDE_DIR}
    ${BATTLESHIP_NETWORKING_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)



add_subdirectory(olc)
