/**
 *  @file   Paratrooper.h
 *  @brief  Paratrooper Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef PARATROOPERS_PARATROOPER_H_
#define PARATROOPERS_PARATROOPER_H_

#include "BaseObject.h"
#include "Bomb.h"

class Arena;

class Paratrooper : public BaseObject {

  friend class Helicopters;

public:
  Paratrooper();
  ~Paratrooper();

  void init(Arena *a);
  void reset(Arena *a);
  void update(Arena *a);
  void evolve(Arena *a);

  int hit(Phase *p);
  void fragment(Phase *p);

  static const char trooper[24];
  static const char parachute[110];

  std::list<PhaseData> objects;

  typedef enum {
    NOPARACHUTE,
    PARACHUTE,
    GROUND,
    GROUNDASSAULT,
    AIRASSAULT,
    FREEFALL
  } State;

  State assault;

private:
  int pwidth, pheight, left, right;

  std::list<PhaseData *> attack;

  int nFallingID;

  Arena *arena;

  Bomb bombs;
};

#include "Arena.h"

#endif
