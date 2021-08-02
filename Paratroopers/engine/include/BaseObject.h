/**
 *  @file   BaseObject.h
 *  @brief  Base Object Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef PARATROOPERS_BASEOBJECT_H_
#define PARATROOPERS_BASEOBJECT_H_

#include "PhaseData.h"
#include <list>

#include "Arena.h"
class BaseObject {

public:
  virtual void init(Arena *a);
  virtual void respond(Arena::Event event, void *sender);
  virtual void evolve(Arena *a);
  virtual void update(Arena *a);
  virtual void reset(Arena *a);

  virtual int hit(Phase *p);
  virtual void fragment(Phase *p);

  int width, height, value;

  std::list<Phase> objects;
  std::list<PhaseData> fragments;
};

#endif
