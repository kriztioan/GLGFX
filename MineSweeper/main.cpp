/**
 *  @file   main.cpp
 *  @brief  Mine Sweeper
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "MineSweeper.h"

int main(int argc, char *argv[]) {

  MineSweeper sfx;

  sfx.ConstructWindow(256, 376, 2, &argc, argv);
  sfx.Start();

  return 0;
}
