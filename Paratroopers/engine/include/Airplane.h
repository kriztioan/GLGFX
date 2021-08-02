/**
 *  @file   Airplane.h
 *  @brief  Airplane Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef PARATROOPERS_AIRPLANE_H_
#define PARATROOPERS_AIRPLANE_H_

#include "Bomb.h"

class Airplane : public BaseObject {

public:
  Airplane();

  void init(Arena *a);
  void evolve(Arena *a);
  void update(Arena *a);

  void fragment(Phase *p);

  static const char airplane_left[126];
  static const char airplane_right[126];

  int flybyID;
  int missileID;

  Bomb bombs;
};

#endif
