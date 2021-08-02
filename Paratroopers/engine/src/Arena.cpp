/**
 *  @file   Arena.h
 *  @brief  Arena Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "Arena.h"

const char *Arena::hexcolors[16] = {"#000000", "#555555", "#0000AA", "#5555FF",
                                    "#00AA00", "#55FF55", "#00AAAA", "#55FFFF",
                                    "#AA0000", "#FF5555", "#AA00AA", "#FF55FF",
                                    "#AA5500", "#FFFF55", "#AAAAAA", "#FFFFFF"};

Arena::Arena()
    : score(0), topscore(0), timer(0.0), state(Arena::FINE),
      threat(Arena::LEVEL0), palette(palette1), DrawPixel(NULL) {

  bevents = 8;
  nevents = 0;
  events = (Event *)malloc(bevents * sizeof(Event));
  events[0] = DONE;

  width = 320;
  height = 240 - 11;

  strncpy(pausestr, "PAUSE", 6);
  strncpy(gameoverstr, "GAME OVER", 10);
  strncpy(continuestr, "PRESS SPACE TO CONTINUE", 25);

  highscores = ".paratroopers";

  std::ifstream ifstr(highscores.c_str());
  if (ifstr.good())
    ifstr >> topscore;
  ifstr.close();

  snprintf(topscorestr, 16, "HIGHSCORE %05i", topscore);

  srand((unsigned int)time(NULL));
}

Arena::~Arena() {

  delete events;

  std::ofstream ofstr(highscores.c_str(), std::ios::out | std::ios::trunc);
  ofstr << topscore;
  ofstr.close();
}

void Arena::AddParticipant(BaseObject *bo) {

  bo->init(this);
  participants.push_back(bo);
}

void Arena::SetResponder(BaseObject *resp) { responder = resp; }

void Arena::AddEvent(Event event) {

  if ((++nevents + 1) == bevents) {
    bevents *= 2;
    events = (Event *)realloc(events, bevents * sizeof(Event));
  }
  events[nevents - 1] = event;
  events[nevents] = DONE;
}

void Arena::RemoveEvent(Event event) {

  for (int i = 0; i < nevents; i++) {
    if (events[i] == event) {
      memmove(events + i, events + i + 1, (nevents - i) * sizeof(Event));
      --nevents;
      break;
    }
  }
}

void Arena::reset() {

  std::list<BaseObject *>::iterator it = participants.begin();
  while (it != participants.end()) {
    (*it)->reset(this);
    ++it;
  }

  palette = palette1;
  score = 0;
  state = Arena::FINE;
  threat = Arena::LEVEL0;
  timer = 0.0;
}

void Arena::update() {

  switch (threat) {

  case Arena::LEVEL0:
    if (timer > 2.0)
      threat = Arena::LEVEL1;
    break;

  case Arena::LEVEL1:
    if (timer > 7.2)
      threat = Arena::LEVEL2;
    break;

  case Arena::LEVEL2:
    if (timer > 8.4) {
      palette = palette2;
      threat = Arena::LEVEL3;
    }
    break;

  case Arena::LEVEL3:
    if (timer > 11.6) {
      timer = 0.0;
      palette = palette1;
      threat = Arena::LEVEL0;
    }
    break;

  case Arena::LOCKED:
    break;
  };

  std::list<BaseObject *>::iterator it = participants.begin();
  while (it != participants.end()) {

    if (state != Arena::PAUSED)
      (*it)->evolve(this);
    (*it)->update(this);
    ++it;
  }
}

void Arena::Draw(const char *src, int src_x, int src_y, int width, int height,
                 int dst_x, int dst_y) {

  int x, y;
  for (int i = src_y; i < height; i++) {
    for (int j = src_x; j < width; j++) {
      x = j + dst_x;
      y = i + dst_y;
      if ((*(src + j + (i * width)) > 0) && x > -1 && x < Arena::width &&
          y > -1 && y < Arena::height) {
        DrawPixel(x, y, (*(src + j + (i * width))));
      }
    }
  }
}

void Arena::DrawRotate(const char *src, int src_x, int src_y, int width,
                       int height, int dst_x, int dst_y, int cen_x, int cen_y,
                       float angle) {

  float a = angle * M_PI / 180.0, m = 1.41 * height, sina = sinf(a),
        cosa = cosf(a);

  int x_org, y_org, x, y;
  for (float i = -m; i < m; i++) {
    for (float j = -m; j < m; j++) {
      x_org = rint((i - cen_y) * sina + (j - cen_x) * cosa + cen_x);
      y_org = rint((i - cen_y) * cosa - (j - cen_x) * sina + cen_y);
      x = j + dst_x;
      y = i + dst_y;

      if (x_org > -1 && x_org < width && y_org > -1 && y_org < height &&
          (*(src + x_org + (y_org * width)) > 0) && x > 0 && x < Arena::width &&
          y > 0 && y < Arena::height) {
        DrawPixel(x, y, (*(src + x_org + (y_org * width))));
      }
    }
  }
}

void Arena::run(float e) {

  elapsed = e;

  Arena::Event *events = this->events, event;

  while ((event = *events++) != Arena::DONE) {

    if (state != Arena::FINE && event != Arena::QUIT) {
      if (state == Arena::PAUSED && event == Arena::SPACE)
        state = Arena::FINE;
      else if (state == Arena::GAMEOVER && event == Arena::SPACE)
        reset();
      continue;
    }

    responder->respond(event, this);

    switch (event) {
    case Arena::FIRE:
    case Arena::LEFT:
    case Arena::RIGHT:
      break;
    case Arena::PAUSE:
      state = Arena::PAUSED;
      break;
    case Arena::QUIT:
    case Arena::DONE:
    case Arena::SPACE:
      break;
    };
  }

  if (score > topscore) {

    topscore = score;

    snprintf(topscorestr, 16, "HIGHSCORE %05i", topscore);
  }

  if (state == Arena::GAMEOVER) {

    DrawString(120, 112, 2, gameoverstr);

    DrawString(64, 136, 3, continuestr);
  } else if (state == Arena::PAUSED) {

    DrawString(140, 112, 2, pausestr);

    DrawString(64, 136, 3, continuestr);
  }

  snprintf(scorestr, 6, "%05i", score);

  DrawString(0, 238, 1, scorestr);

  DrawString(194, 238, 1, topscorestr);

  timer += e;

  update();
}
