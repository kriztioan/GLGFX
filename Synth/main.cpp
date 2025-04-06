/**
 *  @file   main.cpp
 *  @brief  Synth
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Synth.h"

int main(int argc, char *argv[]) {

  Synth gfx;

  gfx.ConstructWindow(320, 280, 2, &argc, argv);
  gfx.Start();

  return 0;
}
