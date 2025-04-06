cmake_minimum_required(VERSION 3.17)
project(Snake LANGUAGES C CXX OBJCXX)

set(CMAKE_CXX_STANDARD 17)

find_library(OPENGL OpenGL)

find_package(GLUT)

find_package(ZLIB)

add_executable(Snake main.cpp Snake.h ../retina_helper.mm ../GLGFX.h ../nesfont8x8.c)

target_link_libraries(Snake ${OPENGL} ${ZLIB_LIBRARIES} ${COREAUDIO} ${AUDIOUNIT} ${GLUT_LIBRARIES})

add_custom_command(TARGET Snake POST_BUILD COMMAND install_name_tool -change /System/Library/Frameworks/GLUT.framework/Versions/A/GLUT /Library/Frameworks/GLUT.framework/Versions/A/GLUT Snake)
