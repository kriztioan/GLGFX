cmake_minimum_required(VERSION 3.17)
project(Breakout LANGUAGES C CXX OBJCXX)

set(CMAKE_CXX_STANDARD 17)

find_library(OPENGL OpenGL)

find_package(GLUT)

find_library(COREAUDIO CoreAudio)

find_library(AUDIOUNIT AudioUnit)

find_package(ZLIB)

add_executable(Breakout main.cpp ../retina_helper.mm ../GLGFX.h ../nesfont8x8.c ../Audio.h ../SampledAudio.h)

target_link_libraries(Breakout ${ZLIB_LIBRARIES} ${OPENGL} ${COREAUDIO} ${AUDIOUNIT} ${GLUT_LIBRARIES})

add_custom_command(TARGET Breakout POST_BUILD COMMAND install_name_tool -change /System/Library/Frameworks/GLUT.framework/Versions/A/GLUT /Library/Frameworks/GLUT.framework/Versions/A/GLUT Breakout)
