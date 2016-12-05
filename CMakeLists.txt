cmake_minimum_required(VERSION 3.6)
project(FInal430)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)
add_executable(FInal430 ${SOURCE_FILES})
find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
target_include_directories(myapp ${OPENGL_INCLUDE_DIR})
target_link_libraries(myapp ${OPENGL_gl_LIBRARY})