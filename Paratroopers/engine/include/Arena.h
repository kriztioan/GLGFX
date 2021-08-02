/**
 *  @file   Arena.h
 *  @brief  Arena Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef PARATROOPERS_ARENA_H_
#define PARATROOPERS_ARENA_H_

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <fstream>
#include <list>
#include <string>

class BaseObject;

class Arena {

public:
  typedef enum { FIRE, LEFT, RIGHT, QUIT, PAUSE, SPACE, DONE } Event;
  typedef enum { FINE, PAUSED, GAMEOVER } State;
  typedef enum { LEVEL0, LEVEL1, LEVEL2, LEVEL3, LOCKED } Threat;

  Arena();
  virtual ~Arena();

  void run(float t);

  void AddParticipant(BaseObject *bo);

  void AddEvent(Event event);

  void RemoveEvent(Event event);

  void SetResponder(BaseObject *responder);

  void SetScore(int score);

  void SetMaxScore(int maxscore);

  int width, height;

  void Draw(const char *src, int src_x, int src_y, int width, int height,
            int dst_x, int dst_y);
  void DrawRotate(const char *src, int src_x, int src_y, int width, int height,
                  int dst_x, int dst_y, int cen_x, int cen_y, float angle);

  int score, topscore;

  float timer, elapsed;

  std::list<BaseObject *> participants;

  State state;
  Threat threat;

  unsigned long *palette;

  void (*DrawPixel)(int x, int y, int color);

  void (*DrawString)(int x, int y, int color, const char *string);

  void (*PlaySound)(int sample, bool loop);

  char (*AddSoundSample)(const char *sample, size_t s_z, size_t s);

private:
  static const char *hexcolors[16];

  unsigned long cgacolors[16];
  unsigned long palette1[4];
  unsigned long palette2[4];

  char scorestr[6], topscorestr[16], pausestr[6], gameoverstr[10],
      continuestr[25];

  Event *events;

  int nevents, bevents;

  std::string highscores;

  BaseObject *responder;

  void update();

  void reset();
};

#include "BaseObject.h"

#endif
