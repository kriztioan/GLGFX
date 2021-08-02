cmake_minimum_required(VERSION 3.17)
project(Destroyer)

set(CMAKE_CXX_STANDARD 17)

find_library(OPENGL OpenGL)

find_package(GLUT)

find_library(COREAUDIO CoreAudio)

find_library(AUDIOUNIT AudioUnit)

find_package(ZLIB)

add_executable(Destroyer main.cpp Destroyer.h ../GLGFX.h ../nesfont8x8.c ../Sprite.h ../Audio.h ../SampledAudio.h)

target_link_libraries(Destroyer ${OPENGL} ${ZLIB_LIBRARIES} ${COREAUDIO} ${AUDIOUNIT} ${GLUT_LIBRARIES})

add_custom_command(TARGET Destroyer POST_BUILD COMMAND install_name_tool -change /System/Library/Frameworks/GLUT.framework/Versions/A/GLUT /Library/Frameworks/GLUT.framework/Versions/A/GLUT Destroyer)
