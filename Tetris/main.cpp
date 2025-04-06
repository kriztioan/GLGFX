/**
 *  @file   main.cpp
 *  @brief  Tetris
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Tetris.h"

int main(int argc, char *argv[]) {

  Tetris gfx;

  gfx.ConstructWindow(164, 240, 4, &argc, argv);
  gfx.Start();

  return 0;
}
