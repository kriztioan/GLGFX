/**
 *  @file   Bomb.h
 *  @brief  Bomb Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Bomb.h"

const char Bomb::bomb[16] = {0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0};

Bomb::Bomb() {
  width = 4;
  height = 4;
  value = 30;
}

void Bomb::update(Arena *a) {

  std::list<Phase>::iterator it = objects.begin();

  while (it != objects.end()) {
    a->Draw(Bomb::bomb, 0, 0, width, height, it->x, it->y);
    ++it;
  }

  std::list<PhaseData>::iterator itf = fragments.begin();
  while (itf != fragments.end()) {
    a->Draw(static_cast<char *>(itf->data), 0, 0, width / 2, 1, itf->x, itf->y);
    ++itf;
  }
}

void Bomb::detect(Arena *a) {

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
        fragment(&(*bit));
        bit = objects.erase(bit);
      } else
        ++bit;
    }
    ++oit;
  }
}

void Bomb::fragment(Phase *p) {

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < 2; j++) {
      fragments.push_back(PhaseData(
          p->x + (j * width) / 2, p->y + i, p->dx + (rand() % 9) - 4, 1, -2,
          const_cast<char *>(Bomb::bomb + (i * width) + (j * width) / 2)));
    }
  }
}