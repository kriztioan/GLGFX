/**
 *  @file   Airplane.h
 *  @brief  Airplane Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Airplane.h"

extern size_t flyby_s;
extern size_t flyby_sz;
extern const unsigned char flyby_z[];

extern size_t missile_s;
extern size_t missile_sz;
extern const unsigned char missile_z[];

const char Airplane::airplane_left[126] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0,
    0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0};

const char Airplane::airplane_right[126] = {
    0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0,
    0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};

Airplane::Airplane() {
  width = 18;
  height = 7;
  value = 11;
}

void Airplane::update(Arena *a) {

  std::list<Phase>::iterator it = objects.begin();

  while (it != objects.end()) {
    if (it->dx > 0)
      a->Draw(Airplane::airplane_right, 0, 0, width, height, it->x, it->y);
    else
      a->Draw(Airplane::airplane_left, 0, 0, width, height, it->x, it->y);
    ++it;
  }

  std::list<PhaseData>::iterator itf = fragments.begin();
  while (itf != fragments.end()) {
    a->Draw(static_cast<char *>(itf->data), 0, 0, width / 2, 1, itf->x, itf->y);
    ++itf;
  }
}

void Airplane::init(Arena *a) {

  flybyID = a->AddSoundSample(reinterpret_cast<const char *>(flyby_z), flyby_sz,
                              flyby_s);
  missileID = a->AddSoundSample(reinterpret_cast<const char *>(missile_z),
                                missile_sz, missile_s);
  a->AddParticipant(&bombs);
}

void Airplane::evolve(Arena *a) {
  static float timer1 = 0.0, timer2 = 0.0;
  timer1 += a->elapsed;
  timer2 += a->elapsed;
  if (a->threat == Arena::LEVEL3 && timer1 > 2.0) {
    switch (rand() % 3) {
    case 0:
      break;
    case 1:
      objects.push_back(Phase(-width, 0, 4, 0, 0));
      a->PlaySound(flybyID, false);
      break;
    case 2:
      objects.push_back(Phase(a->width, height, -4, 0, 0));
      a->PlaySound(flybyID, false);
    }
    timer1 = 0.0;
  }
  BaseObject::evolve(a);

  std::list<Phase>::iterator it = objects.begin();
  if (timer2 > 0.25) {
    while (it != objects.end()) {
      if (rand() % 4 == 0 && a->state == Arena::FINE &&
          ((it->dx > 0 && it->x < a->width / 4) ||
           (it->dx < 0 && it->x > 3 * a->width / 4))) {

        float delta_x = 0.5 * (a->width - width) - it->x,
              delta_y = 1.0 * (a->height - 25) - it->y,
              r = hypot(delta_x, delta_y);

        a->PlaySound(missileID, false);

        bombs.objects.push_back(Phase(it->x + width / 2, it->y + height,
                                      5 * delta_x / r, 0, 5 * delta_y / r));
      }
      ++it;
    }
    timer2 = 0.0;
  }

  bombs.detect(a);
}

void Airplane::fragment(Phase *p) {

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < 2; j++) {
      if (p->dx > 0)
        fragments.push_back(
            PhaseData(p->x + (j * width) / 2, p->y + i,
                      p->dx + (rand() % 9) - 4, 1, p->dy,
                      const_cast<char *>(Airplane::airplane_right +
                                         (i * width) + (j * width) / 2)));
      else
        fragments.push_back(
            PhaseData(p->x + (j * width) / 2, p->y + i,
                      p->dx + (rand() % 9) - 4, 1, p->dy,
                      const_cast<char *>(Airplane::airplane_left + (i * width) +
                                         (j * width) / 2)));
    }
  }
}
