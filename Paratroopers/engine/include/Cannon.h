/**
 *  @file   Cannon.h
 *  @brief  Cannon Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef PARATROOPERS_CANNON_H_
#define PARATROOPERS_CANNON_H_

#include "Bullet.h"

class Cannon : public BaseObject {

public:
  Cannon();

  void init(Arena *a);
  void reset(Arena *a);
  void update(Arena *a);
  void evolve(Arena *a);
  void respond(Arena::Event event, void *sender);

  void fragment(Phase *p);
  int hit(Phase *p);

  void fire(Arena *a);

  static const char turret[108];
  static const char cannon[28];

  int fireID;
  int destroyID;

  Bullet bullets;

  int cwidth, cheight;

  float cangle;

private:
  typedef enum { HIT, FINE } State;

  State state;

  bool destroyed;
};

#endif
