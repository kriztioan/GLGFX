/**
 *  @file   Helicopter.h
 *  @brief  Helicopter Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef PARATROOPERS_HELICOPTER_H_
#define PARATROOPERS_HELICOPTER_H_

#include "Paratrooper.h"

class Helicopter : public BaseObject {

public:
  Helicopter();

  void init(Arena *a);
  void evolve(Arena *a);
  void update(Arena *a);

  void fragment(Phase *p);

  static const char helicopter_left[170];
  static const char helicopter_right[170];

  Paratrooper paratroopers;

  int jumpID;
  int passID;
};

#endif
