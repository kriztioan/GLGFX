cmake_minimum_required(VERSION 3.17)
project(Synth LANGUAGES C CXX OBJCXX)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_search_module(FFTW3 REQUIRED fftw3 IMPORTED_TARGET)

pkg_search_module(FFTW3F REQUIRED fftw3f IMPORTED_TARGET)

find_library(OPENGL OpenGL)

find_package(GLUT)

find_library(COREAUDIO CoreAudio)

find_library(AUDIOUNIT AudioUnit)

find_package(ZLIB)

add_executable(Synth main.cpp ../retina_helper.mm ../GLGFX.h ../nesfont8x8.c ../Sprite.h ../Audio.h Synth.h)

target_link_libraries(Synth ${OPENGL} ${ZLIB_LIBRARIES} ${COREAUDIO} ${AUDIOUNIT} ${GLUT_LIBRARIES} PkgConfig::FFTW3 PkgConfig::FFTW3F)

add_custom_command(TARGET Synth POST_BUILD COMMAND install_name_tool -change /System/Library/Frameworks/GLUT.framework/Versions/A/GLUT /Library/Frameworks/GLUT.framework/Versions/A/GLUT Synth)
