/**
 *  @file   Helicopter.h
 *  @brief  Helicopter Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Helicopter.h"

extern size_t jump_s;
extern size_t jump_sz;
extern const unsigned char jump_z[];

extern size_t pass_s;
extern size_t pass_sz;
extern const unsigned char pass_z[];

const char Helicopter::helicopter_left[170] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 3, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 0, 0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0};

const char Helicopter::helicopter_right[170] = {
    0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
    0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 3, 0, 0, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0,
    0, 0, 2, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};

Helicopter::Helicopter() {
  width = 17;
  height = 10;
  value = 9;
}

void Helicopter::evolve(Arena *a) {
  static float timer1 = 0.0, timer2 = 0.0;
  timer1 += a->elapsed;
  timer2 += a->elapsed;
  if ((a->threat == Arena::LEVEL1 || a->threat == Arena::LOCKED) &&
      timer1 > 1.0) {
    switch (rand() % 3) {
    case 0:
      break;
    case 1:
      objects.push_back(Phase(-width, 0, 3, 0, 0));
      a->PlaySound(passID, false);
      break;
    case 2:
      a->PlaySound(passID, false);
      objects.push_back(Phase(a->width, height, -3, 0, 0));
    }
    timer1 = 0.0;
  }
  BaseObject::evolve(a);

  if (paratroopers.assault == Paratrooper::AIRASSAULT &&
      a->state == Arena::FINE && timer2 > 0.25) {
    std::list<Phase>::iterator it = objects.begin();
    while (it != objects.end()) {
      if (rand() % 3 == 0 &&
          ((it->x > -width / 2 && it->x < 3 * a->width / 8) ||
           (it->x > 5 * a->width / 8 - width - paratroopers.width &&
            it->x < a->width - width / 2 - paratroopers.width))) {

        a->PlaySound(jumpID, false);

        paratroopers.objects.push_back(
            PhaseData(it->x + width / 2, it->y + height / 2, 0, 1, 1,
                      (new Paratrooper::State(Paratrooper::NOPARACHUTE))));
      }
      ++it;
    }
    timer2 = 0.0;
  }
}

void Helicopter::update(Arena *a) {

  std::list<Phase>::iterator it = objects.begin();

  while (it != objects.end()) {
    if (it->dx > 0)
      a->Draw(Helicopter::helicopter_right, 0, 0, width, height, it->x, it->y);
    else
      a->Draw(Helicopter::helicopter_left, 0, 0, width, height, it->x, it->y);
    ++it;
  }

  std::list<PhaseData>::iterator itf = fragments.begin();
  while (itf != fragments.end()) {
    a->Draw(static_cast<char *>(itf->data), 0, 0, width / 2, 1, itf->x, itf->y);
    ++itf;
  }
}

void Helicopter::init(Arena *a) {

  jumpID = a->AddSoundSample(reinterpret_cast<const char *>(jump_z), jump_sz,
                             jump_s);
  passID = a->AddSoundSample(reinterpret_cast<const char *>(pass_z), pass_sz,
                             pass_s);
  a->AddParticipant(&paratroopers);
}

void Helicopter::fragment(Phase *p) {

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < 2; j++) {
      if (p->dx > 0)
        fragments.push_back(
            PhaseData(p->x + (j * width) / 2, p->y + i,
                      p->dx + (rand() % 9) - 4, 1, p->dy,
                      const_cast<char *>(Helicopter::helicopter_right +
                                         (i * width) + (j * width) / 2)));
      else
        fragments.push_back(
            PhaseData(p->x + (j * width) / 2, p->y + i,
                      p->dx + (rand() % 9) - 4, 1, p->dy,
                      const_cast<char *>(Helicopter::helicopter_left +
                                         (i * width) + (j * width) / 2)));
    }
  }
}
