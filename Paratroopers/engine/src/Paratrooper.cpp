/**
 *  @file   Paratrooper.h
 *  @brief  Paratrooper Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Paratrooper.h"

extern size_t falling_s;
extern size_t falling_sz;
extern const unsigned char falling_z[];

const char Paratrooper::trooper[24] = {0, 2, 2, 0, 0, 2, 2, 0, 2, 1, 1, 2,
                                       0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1};

const char Paratrooper::parachute[110] = {
    0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0,
    0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 3,
    0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0};

Paratrooper::Paratrooper()
    : assault(Paratrooper::AIRASSAULT), pwidth(10), pheight(11), left(0),
      right(0) {
  width = 4;
  height = 6;
  value = 2;
}

Paratrooper::~Paratrooper() {

  std::list<PhaseData>::iterator it = objects.begin();
  while (it != objects.end()) {
    delete static_cast<Paratrooper::State *>(it->data);
    ++it;
  }
}

void Paratrooper::init(Arena *a) {
  arena = a;
  nFallingID = arena->AddSoundSample(reinterpret_cast<const char *>(falling_z),
                                     falling_sz, falling_s);
  arena->AddParticipant(&bombs);
}

void Paratrooper::reset(Arena *a) {

  assault = Paratrooper::AIRASSAULT;
  attack.clear();
  left = right = 0;
  std::list<PhaseData>::iterator it = objects.begin();
  while (it != objects.end()) {
    delete static_cast<Paratrooper::State *>(it->data);
    ++it;
  }

  objects.clear();
  BaseObject::reset(a);
}

void Paratrooper::update(Arena *a) {

  std::list<PhaseData>::iterator it = objects.begin();
  while (it != objects.end()) {
    a->Draw(Paratrooper::trooper, 0, 0, width, height, it->x, it->y);
    if (*static_cast<Paratrooper::State *>(it->data) == PARACHUTE)
      a->Draw(Paratrooper::parachute, 0, 0, pwidth, pheight,
              it->x - (pwidth - width) / 2, it->y - pheight);
    ++it;
  }

  it = fragments.begin();
  while (it != fragments.end()) {
    a->Draw(static_cast<char *>(it->data), 0, 0, pwidth / 2, 1, it->x, it->y);
    ++it;
  }
}

void Paratrooper::evolve(Arena *a) {

  bombs.detect(a);

  std::list<PhaseData>::iterator it = objects.begin();
  while (it != objects.end()) {

    if (*static_cast<Paratrooper::State *>(it->data) != Paratrooper::GROUND &&
        *static_cast<Paratrooper::State *>(it->data) != Paratrooper::FREEFALL &&
        it->y > a->height / 5) {
      *static_cast<Paratrooper::State *>(it->data) = Paratrooper::PARACHUTE;
      it->ddy = 0;
      it->dy = 2;
    }

    if (it->y > a->height - height) {

      it->y = a->height - height;
      if (*static_cast<Paratrooper::State *>(it->data) ==
          Paratrooper::FREEFALL) {
        fragment(&(*it));
        delete static_cast<Paratrooper::State *>(it->data);
        it = objects.erase(it);
        continue;
      } else {

        *static_cast<Paratrooper::State *>(it->data) = Paratrooper::GROUND;
        if (it->x > 0 && it->x < 3 * a->width / 8) {
          if (++left > 3) {
            a->threat = Arena::LOCKED;
            assault = GROUNDASSAULT;
          }
        } else if (++right > 3) {
          a->threat = Arena::LOCKED;
          assault = GROUNDASSAULT;
        }

        it->dy = it->ddy = 0;

        if (attack.empty() && assault == GROUNDASSAULT) {

          for (it = objects.begin(); it != objects.end(); it++)
            attack.push_back(&(*it));

          attack.remove_if([this](PhaseData *a) {
            if (*static_cast<Paratrooper::State *>(a->data) !=
                Paratrooper::GROUND)
              return true;
            if (right > 3)
              return (158.0f - a->x) > 0;
            return (158.0f - a->x) < 0;
          });

          attack.sort([](PhaseData *a, PhaseData *b) {
            return fabs(158.0f - a->x) < fabs(158.0f - b->x);
          });

          while (attack.size() > 4)
            attack.pop_back();
        }
      }
    }

    it->x += it->dx * a->elapsed * 32.0;
    it->dy += it->ddy * a->elapsed * 32.0;
    it->y += it->dy * a->elapsed * 32.0;

    ++it;
  }

  it = fragments.begin();
  while (it != fragments.end()) {

    if (it->x < -width || it->x > a->width ||
        it->y + it->dy > a->height - height || it->y < 0) {
      it = fragments.erase(it);
      continue;
    }

    it->x += it->dx * a->elapsed * 32.0;
    it->dy += it->ddy * a->elapsed * 32.0;
    it->y += it->dy * a->elapsed * 32.0;
    ++it;
  }

  if (assault == GROUNDASSAULT && a->state != Arena::GAMEOVER) {

    std::list<PhaseData *>::iterator itp = attack.begin();
    switch (attack.size()) {
    case 0:

      if (a->state != Arena::GAMEOVER) {

        a->state = Arena::GAMEOVER;

        bombs.objects.push_back(Phase(158.0f, 201.0f, 0.0f, 0.0f, 1.0f));
      }
      break;
    case 1:
      if (std::fabs(158.0f - (*itp)->x) > 23.0f) {
        if ((*itp)->x > 158.0f)
          (*itp)->x -= a->elapsed * 32.0;
        else
          (*itp)->x += a->elapsed * 32.0;
      } else if ((*itp)->y > 216.0f)
        (*itp)->y -= a->elapsed * 32.0;
      else if (std::fabs(158.0f - (*itp)->x) > 17.0f) {
        if ((*itp)->x > 158.0f)
          (*itp)->x -= a->elapsed * 32.0;
        else
          (*itp)->x += a->elapsed * 32.0;
      } else if ((*itp)->y > 208.0f)
        (*itp)->y -= a->elapsed * 32.0;
      else
        attack.remove(*itp);
      break;
    case 2:
      if (std::fabs(158.0f - (*itp)->x) > 23.0f) {
        if ((*itp)->x > 158.0f)
          (*itp)->x -= a->elapsed * 32.0;
        else
          (*itp)->x += a->elapsed * 32.0;
      } else
        attack.remove(*itp);
      break;
    case 3:
      if (std::fabs(158.0f - (*itp)->x) > 17.0f) {
        if ((*itp)->x > 158.0f)
          (*itp)->x -= a->elapsed * 32.0;
        else
          (*itp)->x += a->elapsed * 32.0;
      } else if ((*itp)->y > 216.0f)
        (*itp)->y -= a->elapsed * 32.0;
      else
        attack.remove(*itp);
      break;
    case 4:
      if (std::fabs(158.0f - (*itp)->x) > 17.0f) {
        if ((*itp)->x > 158.0f)
          (*itp)->x -= a->elapsed * 32.0;
        else
          (*itp)->x += a->elapsed * 32.0;
      } else
        attack.remove(*itp);
    }
  }
}

int Paratrooper::hit(Phase *p) {

  std::list<PhaseData>::iterator it = objects.begin();
  while (it != objects.end()) {

    if (*static_cast<Paratrooper::State *>(it->data) == PARACHUTE &&
        p->x > it->x - (pwidth - width) / 2 &&
        p->x < it->x + (3 * pwidth - width) / 2 && p->y < it->y &&
        p->y > it->y - pheight) {
      arena->PlaySound(nFallingID, false);
      *static_cast<Paratrooper::State *>(it->data) = FREEFALL;
      it->ddy = 1;
      return (6);
    }

    if (p->x > it->x && p->x < it->x + width && p->y < it->y + height &&
        p->y > it->y) {
      fragment(&(*it));
      it = objects.erase(it);
      return (value);
    } else
      ++it;
  }

  return (-1);
}

void Paratrooper::fragment(Phase *p) {

  for (int i = 0; i < width / 2; i++) {
    for (int j = 0; j < 2; j++) {
      fragments.push_back(PhaseData(
          p->x + (j * width) / 2, p->y + i, p->dx + (rand() % 9) - 4, 1, -2,
          const_cast<char *>(trooper + (i * width) + (j * width) / 2)));
    }
  }
}
