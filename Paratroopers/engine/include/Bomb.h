/**
 *  @file   Bomb.h
 *  @brief  Bomb Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef PARATROOPERS_BOMB_H_
#define PARATROOPERS_BOMB_H_

#include "BaseObject.h"

class Bomb : public BaseObject {

public:
  Bomb();

  void update(Arena *a);
  void detect(Arena *a);

  void fragment(Phase *p);

  static const char bomb[16];
};

#endif
