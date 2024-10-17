/**
 *  @file   main.cpp
 *  @brief  Breakout Game
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2023-11-08
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Breakout.h"

int main(int argc, char *argv[]) {

  Breakout gfx;

  gfx.ConstructWindow(200, 320, 4, &argc, argv);
  gfx.Start();

  return 0;
}
