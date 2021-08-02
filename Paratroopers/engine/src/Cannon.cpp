/**
 *  @file   Cannon.h
 *  @brief  Cannon Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Cannon.h"

    extern size_t fire_s;
extern size_t fire_sz;
extern const unsigned char fire_z[];

extern size_t destroy_s;
extern size_t destroy_sz;
extern const unsigned char destroy_z[];

const char Cannon::turret[108] = {
    0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 2, 2, 0,
    1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

const char Cannon::cannon[28] = {0, 3, 3, 0, 0, 3, 3, 0, 3, 3, 3, 3, 3, 3,
                                 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

Cannon::Cannon() : cwidth(4), cheight(7), cangle(90.0), state(Cannon::FINE) {
  width = 12;
  height = 9;
  value = 0;
}

void Cannon::init(Arena *a) {

  destroyed = false;
  objects.push_back(Phase((a->width - width) / 2, a->height - height - 18,
                          a->width, 0, a->height));
  a->AddParticipant(&bullets);
  fireID = a->AddSoundSample(reinterpret_cast<const char *>(fire_z), fire_sz,
                             fire_s);
  destroyID = a->AddSoundSample(reinterpret_cast<const char *>(destroy_z),
                                destroy_sz, destroy_s);
  a->SetResponder(this);
}

void Cannon::reset(Arena *a) {

  cangle = 90.0;
  state = Cannon::FINE;
}

void Cannon::evolve(Arena *a) {

  if (destroyed) {
    a->PlaySound(destroyID, false);
    destroyed = false;
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

  bullets.detect(a);
}

void Cannon::update(Arena *a) {

  if (Cannon::state == Cannon::HIT) {
    Cannon::state = FINE;
    a->state = Arena::GAMEOVER;
  }

  if (a->state != Arena::GAMEOVER) {
    a->Draw(turret, 0, 0, width, height, (a->width - width) / 2,
            a->height - height - 18);
    a->DrawRotate(cannon, 0, 0, cwidth, cheight, (a->width - cwidth) / 2,
                  a->height - height - cheight - 17, cwidth / 2, cheight,
                  90.0 - cangle);
  }

  std::list<PhaseData>::iterator itf = fragments.begin();
  while (itf != fragments.end()) {
    a->Draw(static_cast<char *>(itf->data), 0, 0, width / 2, 1, itf->x, itf->y);
    ++itf;
  }
}

void Cannon::fire(Arena *a) {
  static float timer = 0.0;
  timer += a->elapsed;
  if (timer > 0.08 && a->state == Arena::FINE) {

    a->PlaySound(fireID, false);

    if (--(a->score) < 0)
      a->score = 0;

    float angle = M_PI * cangle / 180.0, sina = sinf(angle), cosa = cosf(angle);

    bullets.objects.push_back(Phase((a->width / 2) + cheight * cosa,
                                    a->height - 17 - height - cheight * sina,
                                    6 * cosa, 0, -6 * sina));

    timer = 0.0;
  }
}

int Cannon::hit(Phase *p) {

  std::list<Phase>::iterator it = objects.begin();

  if (p->x > it->x && p->x < it->x + width && p->y > it->y &&
      p->y < it->y + height) {

    if (Cannon::state != Cannon::HIT) {
      Cannon::state = Cannon::HIT;
      Phase ph(it->x, it->y, 0, 0, 0);
      fragment(&ph);
      destroyed = true;
    }
    return (0);
  } else
    return (-1);
}

void Cannon::fragment(Phase *p) {

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < 2; j++) {
      fragments.push_back(PhaseData(
          p->x + (j * width) / 2, p->y + i, (rand() % 9) - 4, 1, -10,
          const_cast<char *>(Cannon::turret + (i * width) + (j * width) / 2)));
    }
  }
}

void Cannon::respond(Arena::Event event, void *sender) {

  Arena *a = (Arena *)sender;

  switch (event) {

  case Arena::FIRE:
    fire(a);
    break;

  case Arena::LEFT:
    cangle += 100.0 * a->elapsed;
    break;

  case Arena::RIGHT:
    cangle -= 100.0 * a->elapsed;
    break;

  default:
    break;
  }

  if (cangle > 180.0)
    cangle = 180.0;
  else if (cangle < 0.0)
    cangle = 0.0;
}
