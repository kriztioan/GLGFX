/**
 *  @file   Phase.h
 *  @brief  Phase Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Phase.h"

Phase::Phase() { x = y = dx = ddy = dy = 0; }

Phase::Phase(float x, float y, float dx, float dyy, float dy)
    : x(x), y(y), dx(dx), ddy(dyy), dy(dy) {}
