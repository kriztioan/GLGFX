/**
 *  @file   main.cpp
 *  @brief  Destroyer Game
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Destroyer.h"

int main(int argc, char *argv[]) {

  Destroyer gfx;

  gfx.ConstructWindow(320, 200, 3, &argc, argv);
  gfx.Start();

  return 0;
}
