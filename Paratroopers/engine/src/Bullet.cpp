/**
 *  @file   Bullet.h
 *  @brief  Bullet Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Bullet.h"

const char Bullet::bullet[1] = {1};

Bullet::Bullet() {
  width = 1;
  height = 1;
  value = 0;
}

void Bullet::update(Arena *a) {

  std::list<Phase>::iterator it = objects.begin();

  while (it != objects.end()) {
    a->Draw(Bullet::bullet, 0, 0, width, height, it->x, it->y);
    ++it;
  }
}

void Bullet::detect(Arena *a) {

  int points;

  std::list<BaseObject *>::iterator oit = a->participants.begin();
  while (oit != a->participants.end()) {
    if (this == *oit) {
      ++oit;
      continue;
    }
    std::list<Phase>::iterator bit = objects.begin();
    while (bit != objects.end()) {
      if ((points = (*oit)->hit(&(*bit))) > -1) {
        a->score += points;
        bit = objects.erase(bit);
      } else
        ++bit;
    }
    ++oit;
  }
}
