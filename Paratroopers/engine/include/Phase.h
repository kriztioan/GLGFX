/**
 *  @file   Phase.h
 *  @brief  Phase Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef PARATROOPERS_PHASE_H_
#define PARATROOPERS_PHASE_H_

class Phase {

public:
  Phase();
  Phase(float x, float y, float dx, float ddy, float dy);

  float x, y, dx, ddy, dy;
};

#endif
