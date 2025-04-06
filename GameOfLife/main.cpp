/**
 *  @file   main.cpp
 *  @brief  Game of Life
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "GameOfLife.h"

int main(int argc, char *argv[]) {

  GameOfLife gfx;

  gfx.ConstructWindow(320, 240, 4, &argc, argv);
  gfx.Start();

  return 0;
}
