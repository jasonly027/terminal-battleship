cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(battleship
    VERSION 1.0
    LANGUAGES CXX
)

add_subdirectory(external/networking)



add_executable(${PROJECT_NAME}
    src/main.cpp
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    battleship_networking
)
target_link_libraries(${PROJECT_NAME}
    battleship_networking
)



# Set using Asio without Boost
add_definitions(-DASIO_STANDALONE)
# Set minimum Windows version for Windows SDK
add_definitions(-D_WIN32_WINNT=0x0A00) # 0x0A00 = Win10