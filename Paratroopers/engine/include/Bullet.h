/**
 *  @file   Bullet.h
 *  @brief  Bullet Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef PARATROOPERS_BULLET_H_
#define PARATROOPERS_BULLET_H_

#include "BaseObject.h"

class Bullet : public BaseObject {

  friend class Cannon;

public:
  Bullet();

  void update(Arena *a);
  void detect(Arena *a);

  static const char bullet[1];
};

#endif
