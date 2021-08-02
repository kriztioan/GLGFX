/**
 *  @file   Paratroopers.h
 *  @brief  Paratroopers in CBGLGFX
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGFX_PARATROOPERS_H_
#define CBGLGFX_PARATROOPERS_H_

#include "../GLGFX.h"
#include "../SampledAudio.h"
#include "../Sprite.h"

#include "Airplane.h"
#include "Arena.h"
#include "Cannon.h"
#include "Helicopter.h"
#include "Ufo.h"

class Paratroopers : public cb::GLGFX {

  bool OnUserCreate() override {

    arena = new Arena;
    arena->DrawPixel = m_DrawPixel;
    arena->DrawString = m_DrawString;
    arena->AddSoundSample = m_AddSoundSample;
    arena->PlaySound = m_PlaySound;
    cannon = new Cannon;
    arena->AddParticipant(cannon);
    helicopters = new Helicopter;
    arena->AddParticipant(helicopters);
    airplanes = new Airplane;
    arena->AddParticipant(airplanes);
    ufos = new Ufo;
    arena->AddParticipant(ufos);

    audio.SetAudioSamplerate(44100);
    audio.SetAudioStereo(2);
    audio.SetAudioChannels(64);
    audio.SetBitsPerChannel(8);
    audio.SetVolume(50);
    audio.Start();

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override {

    if (KeyUp('q'))
      return false;

    if (KeySpecialDown(GLUT_KEY_UP))
      arena->AddEvent(Arena::FIRE);
    if (KeySpecialDown(GLUT_KEY_LEFT))
      arena->AddEvent(Arena::LEFT);
    if (KeySpecialDown(GLUT_KEY_RIGHT))
      arena->AddEvent(Arena::RIGHT);
    if (KeyDown('p'))
      arena->AddEvent(Arena::PAUSE);
    if (KeyDown(' '))
      arena->AddEvent(Arena::SPACE);

    if (KeySpecialUp(GLUT_KEY_UP))
      arena->RemoveEvent(Arena::FIRE);
    if (KeySpecialUp(GLUT_KEY_LEFT))
      arena->RemoveEvent(Arena::LEFT);
    if (KeySpecialUp(GLUT_KEY_RIGHT))
      arena->RemoveEvent(Arena::RIGHT);
    if (KeyUp('p'))
      arena->RemoveEvent(Arena::PAUSE);
    if (KeyUp(' '))
      arena->RemoveEvent(Arena::SPACE);

    Clear(FG_BLACK);

    DrawLine(0, 229, 320, 229, FG_BLUE);

    DrawFilledRectangle(145, 211, 173, 228, FG_GREEN);

    arena->run(fElapsedTime);

    return true;
  }

  static void m_DrawPixel(int x, int y, int color) {

    me->DrawPixel(x, y, color);
  }

  static void m_DrawString(int x, int y, int color, const char *text) {

    me->DrawString(x, y - 7, text, color);
  }

  static void m_PlaySound(int sample, bool loop) { audio.Play(sample, loop); }

  static char m_AddSoundSample(const char *sample, size_t s_z, size_t s) {

    return static_cast<char>(audio.z_Load(sample, s_z, s));
  }

  void OnUserDestroy() override {
    delete arena;
    delete cannon;
    delete helicopters;
    delete airplanes;
    delete ufos;
  }

  Arena *arena;
  Cannon *cannon;
  Helicopter *helicopters;
  Airplane *airplanes;
  Ufo *ufos;

  static cb::SampledAudio audio;

public:
  Paratroopers() {
    sTitle = "Paratroopers";
    bShowFPS = false;
  }
};

cb::SampledAudio Paratroopers::audio;

#endif // CBGLGFX_PARATROOPERS_H_
