/**
 *  @file   Ufo.h
 *  @brief  Ufo Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Ufo.h"

extern size_t et_s;
extern size_t et_sz;
extern const unsigned char et_z[];

const char Ufo::ufo[170] = {
    0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0};

Ufo::Ufo() {
  width = 17;
  height = 10;
  value = 100;
}

void Ufo::init(Arena *a) {
  etID = a->AddSoundSample(reinterpret_cast<const char *>(et_z), et_sz, et_s);
}

void Ufo::evolve(Arena *a) {
  static float timer = 0.0;
  timer += a->elapsed;
  if (timer > 3) {
    switch (rand() % 3) {
    case 0:
      break;
    case 1:
      a->PlaySound(etID, false);
      objects.push_back(Phase(-width, 0, 2, 0, 0));
      break;
    case 2:
      a->PlaySound(etID, false);
      objects.push_back(Phase(a->width, height, -2, 0, 0));
    }
    timer = 0.0;
  }
  BaseObject::evolve(a);
}

void Ufo::update(Arena *a) {

  std::list<Phase>::iterator it = objects.begin();
  while (it != objects.end()) {
    a->Draw(Ufo::ufo, 0, 0, width, height, it->x, it->y);
    ++it;
  }

  std::list<PhaseData>::iterator itf = fragments.begin();
  while (itf != fragments.end()) {
    a->Draw(static_cast<char *>(itf->data), 0, 0, width / 2, 1, itf->x, itf->y);
    ++itf;
  }
}

void Ufo::fragment(Phase *p) {

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < 2; j++) {
      fragments.push_back(PhaseData(
          p->x + (j * width) / 2, p->y + i, p->dx + (rand() % 9) - 4, 1, p->dy,
          const_cast<char *>(Ufo::ufo + (i * width) + (j * width) / 2)));
    }
  }
}
