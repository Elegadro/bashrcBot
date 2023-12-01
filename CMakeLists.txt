cmake_minimum_required(VERSION 3.22)    

project(bashrc VERSION 1.0 DESCRIPTION ".bashrc bot")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

include_directories(inc)

find_package(DPP REQUIRED)

target_link_libraries(${PROJECT_NAME} ${DPP_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE ${DPP_INCLUDE_DIRS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)