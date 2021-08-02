/**
 *  @file   main.cpp
 *  @brief  GFX Engine
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "GFXEngine.h"

int main(int argc, char *argv[]) {

  GFXEngine gfx(argc, argv);

  gfx.ConstructWindow(1920, 1080, 1, &argc, argv);

  gfx.Start();
}
