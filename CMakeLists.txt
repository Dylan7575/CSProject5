cmake_minimum_required(VERSION 3.6)
project(FInal430)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenGL REQUIRED)
find_package(GLUT)
set(SOURCE_FILES main.c)
add_executable(FInal430 ${SOURCE_FILES})
add_subdirectory(/Users/dylanlafrenz/ClionProjects/FInal430/GLFW)
include_directories(/Users/dylanlafrenz/ClionProjects/FInal430/GLFW/include)
target_link_libraries(FInal430 glfw ${GLFW_LIBRARIES})

include_directories( ${OPENGL_INCLUDE_DIRS})
target_link_libraries(FInal430 ${OPENGL_LIBRARIES})




