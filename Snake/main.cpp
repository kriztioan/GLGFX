/**
 *  @file   main.c
 *  @brief  Snake Game
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-09-21
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Snake.h"

int main(int argc, char *argv[]) {

  Snake gfx;

  gfx.ConstructWindow(160, 240, 4, &argc, argv);
  gfx.Start();

  return 0;
}
