cmake_minimum_required(VERSION 3.17)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)

find_library(OPENGL OpenGL)

find_package(GLUT)

find_library(COREAUDIO CoreAudio)

find_library(AUDIOUNIT AudioUnit)

find_package(ZLIB)

add_executable(GameOfLife main.cpp GameOfLife.h ../GLGFX.h ../nesfont8x8.c ../Sprite.h)

target_link_libraries(GameOfLife ${OPENGL} ${ZLIB_LIBRARIES} ${COREAUDIO} ${AUDIOUNIT} ${GLUT_LIBRARIES})

add_custom_command(TARGET GameOfLife POST_BUILD COMMAND install_name_tool -change /System/Library/Frameworks/GLUT.framework/Versions/A/GLUT /Library/Frameworks/GLUT.framework/Versions/A/GLUT GameOfLife)
