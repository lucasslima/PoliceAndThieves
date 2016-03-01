cmake_minimum_required(VERSION 3.3)
project(PoliceAndThieves)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(OpenGL)
find_package(GLUT)

if(CMAKE_BUILD_TOOL MATCHES "(make)")
    add_definitions(-Wall)
endif()

set(SOURCE_FILES
    block.cpp
    block.h
    car.cpp
    car.h
    drawutils.cpp
    drawutils.h
    hideoutblock.cpp
    hideoutblock.h
    highspeedblock.cpp
    highspeedblock.h
    lowspeedblock.cpp
    lowspeedblock.h
    main.cpp
    wallblock.cpp
    wallblock.h
    world.cpp
    world.h)
add_executable(PoliceAndThieves ${SOURCE_FILES})
SET(CMAKE_REQUIRED_LIBRARIES ${GLUT_LIBRARY} ${GL_LIBRARY})
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(PoliceAndThieves ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )