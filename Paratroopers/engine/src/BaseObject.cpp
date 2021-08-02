/**
 *  @file   BaseObject.h
 *  @brief  Base Object Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "BaseObject.h"

void BaseObject::reset(Arena *a) {

  objects.clear();
  fragments.clear();
}

void BaseObject::evolve(Arena *a) {

  std::list<Phase>::iterator it = objects.begin();
  while (it != objects.end()) {

    if (it->x < -width || it->x > a->width ||
        it->y + it->dy > a->height - height || it->y < 0) {
      it = objects.erase(it);
      continue;
    }

    it->x += it->dx * a->elapsed * 32.0;
    it->dy += it->ddy * a->elapsed * 32.0;
    it->y += it->dy * a->elapsed * 32.0;

    ++it;
  }

  std::list<PhaseData>::iterator itf = fragments.begin();
  while (itf != fragments.end()) {

    if (itf->x < -width || itf->x > a->width ||
        itf->y + itf->dy > a->height - height || itf->y < 0) {
      itf = fragments.erase(itf);
      continue;
    }

    itf->x += itf->dx * a->elapsed * 32.0;
    itf->dy += itf->ddy * a->elapsed * 32.0;
    itf->y += itf->dy * a->elapsed * 32.0;
    ++itf;
  }
}

void BaseObject::respond(Arena::Event event, void *sender) {}

void BaseObject::update(Arena *a) {}

void BaseObject::init(Arena *a) {}

int BaseObject::hit(Phase *p) {

  std::list<Phase>::iterator it = objects.begin();
  while (it != objects.end()) {

    if (p->x > it->x && p->x < it->x + width + it->dx &&
        p->y < it->y + height && p->y > it->y) {

      fragment(&(*it));
      it = objects.erase(it);
      return (value);
    } else
      ++it;
  }

  return (-1);
}

void BaseObject::fragment(Phase *p) {}
