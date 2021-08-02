/**
 *  @file   main.c
 *  @brief  Paratroopers
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Paratroopers.h"

int main(int argc, char *argv[]) {

  Paratroopers gfx;

  gfx.ConstructWindow(319, 239, 6, &argc, argv);

  gfx.Start();

  return 0; // never reached
}
