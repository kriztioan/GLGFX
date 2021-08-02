/**
 *  @file   main.c
 *  @brief  Flappy Bird Game
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "FlappyBird.h"

int main(int argc, char *argv[]) {

  FlappyBird gfx;

  gfx.ConstructWindow(320, 200, 6, &argc, argv);
  gfx.Start();

  return 0;
}