/**
 *  @file   Ufo.h
 *  @brief  Ufo Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef PARATROOPERS_UFO_H_
#define PARATROOPERS_UFO_H_

#include "BaseObject.h"

class Ufo : public BaseObject {

public:
  Ufo();

  void init(Arena *a);
  void evolve(Arena *a);
  void update(Arena *a);

  void fragment(Phase *p);

  static const char ufo[170];

  int etID;
};

#endif
