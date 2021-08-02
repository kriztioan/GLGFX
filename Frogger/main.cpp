/**
 *  @file   main.c
 *  @brief  Frogger Game
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Frogger.h"

int main(int argc, char *argv[]) {

  Frogger gfx;

  gfx.ConstructWindow(128, 80, 8, &argc, argv);
  gfx.Start();

  return 0;
}
