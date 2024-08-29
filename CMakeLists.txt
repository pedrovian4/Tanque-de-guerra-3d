cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(TheMiniTank)

add_executable(TheMiniTank 
main.cpp
src/Helpers.cpp
src/Tank.cpp
src/Turret.cpp
src/Track.cpp
src/Scene.cpp

)

include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories(${PROJECT_SOURCE_DIR}/libs)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})

add_library(glad STATIC ${PROJECT_SOURCE_DIR}/libs/glad.c)

target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/libs)

target_link_libraries(TheMiniTank glad ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})