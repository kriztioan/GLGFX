cmake_minimum_required(VERSION 3.17)
project(Tetris LANGUAGES C CXX OBJCXX)

set(CMAKE_CXX_STANDARD 17)

find_library(OPENGL OpenGL)

find_package(GLUT)

find_library(COREAUDIO CoreAudio)

find_library(AUDIOUNIT AudioUnit)

find_package(ZLIB)

add_executable(Tetris main.cpp Tetris.h ../retina_helper.mm ../GLGFX.h ../Sprite.h ../Audio.h ../SampledAudio.h ../nesfont8x8.c sfx/tada.c sfx/bounce.c sfx/tick.c gfx/castle.c gfx/taj.c gfx/skyline.c gfx/forest.c sfx/gameover.c gfx/island.c gfx/wolf.c)

target_link_libraries(Tetris ${OPENGL} ${ZLIB_LIBRARIES} ${COREAUDIO} ${AUDIOUNIT} ${GLUT_LIBRARIES})

add_custom_command(TARGET Tetris POST_BUILD COMMAND install_name_tool -change /System/Library/Frameworks/GLUT.framework/Versions/A/GLUT /Library/Frameworks/GLUT.framework/Versions/A/GLUT Tetris)
