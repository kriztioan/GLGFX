/**
 *  @file   Breakout.h
 *  @brief  Breakout in GLGFX
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2023-11-08
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGFX_BREAKOUT_H_
#define CBGLGFX_BREAKOUT_H_

#include "../GLGFX.h"
#include "../SampledAudio.h"

// Speed up ball every 50 points?

#include <array>
#include <cstdlib>
#include <sstream>

struct sBrick {
  int x;
  int y;
  int w;
  int h;
  int color;
  int points;
  bool active;
};

class Breakout : public cb::GLGFX {

public:
  Breakout() {
    sTitle = "Breakout";
    bShowFPS = false;
  }

private:
  bool OnUserCreate() final {
    GameOverSample = Audio.LoadFromFile("sfx/gameover.raw");
    LostSample = Audio.LoadFromFile("sfx/lost.raw");
    LevelUpSample = Audio.LoadFromFile("sfx/levelup.raw");
    PaddleSample = Audio.LoadFromFile("sfx/paddle.raw");
    BreakSample = Audio.LoadFromFile("sfx/break.raw");

    Audio.SetAudioSamplerate(22050);
    Audio.SetAudioStereo(1);
    Audio.SetAudioChannels(64);
    Audio.SetBitsPerChannel(8);
    Audio.SetVolume(25);
    Audio.Start();

    Reset();

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) final {

    UserInput(fElapsedTime);
    if (bGameMode && !bPaused) {
      Logic(fElapsedTime);
    }
    DrawScreen();
    return !bFinished;
  }

  void Logic(float fElapsedTime) {
    if (nActive == 0) {
      Audio.Play(LevelUpSample);

      float w = sPaddle.w;
      if (sPaddle.w > sBall.r) {
        sPaddle.w = 3.0f * sPaddle.w / 4.0f;
        if (sPaddle.w < sBall.r) {
          sPaddle.w = sBall.r;
        }

        sPaddle.x += (w - sPaddle.w) / 2.0f;
      }
      nRound += 1;
      InitBricks();

      return;
    }

    float fDeltaXPos = 10.0f * sBall.dx * fElapsedTime;
    float fDeltaYPos = 10.0f * sBall.dy * fElapsedTime;
    float m = fDeltaYPos / fDeltaXPos;
    float b = sBall.y - m * sBall.x;

    float fBallNewXPos = sBall.x + fDeltaXPos;
    float fBallNewYPos = sBall.y + fDeltaYPos;

    // Paddle top
    if (sBall.dy > 0.0f && (sPaddle.y - sBall.r) >= sBall.y &&
        (sPaddle.y - sBall.r) <= fBallNewYPos) {
      float fXHit = (sPaddle.y - sBall.r - b) / m;
      if (fXHit >= (sPaddle.x - sBall.r) &&
          fXHit <= (sPaddle.x + sPaddle.w + sBall.r)) {
        Audio.Play(PaddleSample);
        sBall.x = fXHit;
        sBall.y = sPaddle.y - sBall.r;
        sBall.dy = -sBall.dy;
        return;
      }
    }

    // Paddle left
    if (sBall.dx > 0.0f && (sPaddle.x - sBall.r) >= sBall.x &&
        (sPaddle.x - sBall.r) <= fBallNewXPos) {
      float fYHit = (sPaddle.x - sBall.r) * m + b;
      if (fYHit >= (sPaddle.y - sBall.r) &&
          fYHit <= (sPaddle.y + sPaddle.h + sBall.r)) {
        Audio.Play(PaddleSample);
        sBall.x = sPaddle.x - sBall.r;
        sBall.y = fYHit;
        sBall.dx = -sBall.dx;
        return;
      }
    }
    // Paddle right
    else if ((sPaddle.x + sPaddle.w + sBall.r) >= fBallNewXPos &&
             (sPaddle.x + sPaddle.w + sBall.r) <= sBall.x) {
      float fYHit = (sPaddle.x + sPaddle.w + sBall.r) * m + b;
      if (fYHit >= (sPaddle.y - sBall.r) &&
          fYHit <= (sPaddle.y + sPaddle.h + sBall.r)) {
        Audio.Play(PaddleSample);
        sBall.x = sPaddle.x + sPaddle.w + sBall.r;
        sBall.y = fYHit;
        sBall.dx = -sBall.dx;
        return;
      }
    }

    // Left wall
    if (sBall.dx < 0.0f) {
      if (fBallNewXPos < sBall.r) {
        Audio.Play(PaddleSample);
        sBall.x = sBall.r;
        sBall.y = m * sBall.r + b;
        sBall.dx = -sBall.dx;
        return;
      }
    }
    // Right wall
    else if ((fBallNewXPos + sBall.r) > ScreenWidth()) {
      Audio.Play(PaddleSample);
      sBall.x = ScreenWidth() - sBall.r;
      sBall.y = m * fBallNewXPos + b;
      sBall.dx = -sBall.dx;
      return;
    }

    // Top wall
    if (sBall.dy < 0.0f) {
      if (fBallNewYPos < sBall.r) {
        Audio.Play(PaddleSample);
        sBall.y = sBall.r;
        sBall.x = (fBallNewYPos - b) / m;
        sBall.dy = -sBall.dy;
        return;
      }
    }
    // Bottom die
    if (sBall.dy > 0.0f) {
      if ((fBallNewYPos + sBall.r) > ScreenHeight() && bGameMode) {
        --nBalls;
        if (nBalls == 0) {

          Audio.Play(GameOverSample);
        } else {

          Audio.Play(LostSample);
        }
        sBall.y = ScreenHeight() + 2 * sBall.r;
        bGameMode = false;
        return;
      }
    }

    // Bricks
    for (auto &brick : aBricks) {
      if (brick.active) {

        // Bottom
        if (sBall.dy < 0.0f && (brick.y + brick.h + sBall.r) >= fBallNewYPos &&
            (brick.y + brick.h + sBall.r) <= sBall.y) {
          float fXHit = (brick.y + brick.h + sBall.r - b) / m;
          if (fXHit >= (brick.x - sBall.r) &&
              fXHit <= (brick.x + brick.w + sBall.r)) {
            BrickHit(brick);
            sBall.x = fXHit;
            sBall.y = brick.y + brick.h + sBall.r;
            sBall.dy = -sBall.dy;
            return;
          }
        }
        // Top
        else if ((brick.y - sBall.r) >= sBall.y &&
                 (brick.y - sBall.r) <= fBallNewYPos) {
          float fXHit = (brick.y - sBall.r - b) / m;
          if (fXHit >= (brick.x - sBall.r) &&
              fXHit <= (brick.x + brick.w + sBall.r)) {
            BrickHit(brick);
            sBall.x = fXHit;
            sBall.y = brick.y - sBall.r;
            sBall.dy = -sBall.dy;
            return;
          }
        }

        // Left
        if (sBall.dx > 0.0f && (brick.x - sBall.r) >= sBall.x &&
            (brick.x - sBall.r) <= fBallNewXPos) {
          float fYHit = (brick.x - sBall.r) * m + b;
          if (fYHit >= (brick.y - sBall.r) &&
              fYHit <= (brick.y + brick.h + sBall.r)) {
            BrickHit(brick);
            sBall.x = brick.x - sBall.r;
            sBall.y = fYHit;
            sBall.dx = -sBall.dx;
            return;
          }
        }
        // Right
        else if ((brick.x + brick.w + sBall.r) >= fBallNewXPos &&
                 (brick.x + brick.w + sBall.r) <= sBall.x) {
          float fYHit = (brick.x + brick.w + sBall.r) * m + b;
          if (fYHit >= (brick.y - sBall.r) &&
              fYHit <= (brick.y + brick.h + sBall.r)) {
            BrickHit(brick);
            sBall.x = brick.x + brick.w + sBall.r;
            sBall.y = fYHit;
            sBall.dx = -sBall.dx;
            return;
          }
        }
      }
    }

    sBall.x = fBallNewXPos;
    sBall.y = fBallNewYPos;
  }

  void BrickHit(sBrick &brick) {
    Audio.Play(BreakSample);
    brick.active = false;
    --nActive;
    nScore += brick.points;
    if ((nScore - nPrevScore) >= 25) {
      nPrevScore = 25 * (nScore / 25);
      sBall.dx *= 1.1;
      sBall.dy *= 1.1;
    }
  }

  void UserInput(float fElapsedTime) {
    if (KeyUp('q')) {

      bFinished = true;
      return;
    }

    if (bMouse) {
      int nMouseX;
      int nMouseY;

      MousePosition(nMouseX, nMouseY);

      sPaddle.x = nMouseX;
      if (sPaddle.x + sPaddle.w > ScreenWidth()) {

        sPaddle.x = ScreenWidth() - sPaddle.w - 1.0f;
      }
    } else {

      if (KeyPressed(',')) {

        sPaddle.x -= 250.0f * fElapsedTime;
        if (sPaddle.x < 0.0f) {

          sPaddle.x = 0.0;
        }
      }

      if (KeyPressed('.')) {

        sPaddle.x += 250.0f * fElapsedTime;
        if (sPaddle.x + sPaddle.w > ScreenWidth()) {

          sPaddle.x = ScreenWidth() - sPaddle.w - 1.0f;
        }
      }
    }

    if (KeyUp('f')) {

      bShowFPS = !bShowFPS;
    }

    if (bGameMode && KeyUp('p')) {

      bPaused = !bPaused;
    }

    if (KeyUp('m')) {

      bMouse = !bMouse;
    }

    if (!bGameMode && KeyUp(' ')) {

      if (nBalls == 0) {
        Reset();
      } else {
        InitBall();
      }
      bGameMode = true;
    }

    if (KeyUp('r')) {
      Reset();
    }
  }

  void Reset() {

    nRound = 1;
    nScore = nPrevScore = 0;
    nBalls = 3;

    InitPaddle();
    InitBall();
    InitBricks();
  }

  void DrawScreen() {

    Clear(FG_BLUE);

    DrawLine(0, 0, ScreenWidth() - 1, 0, FG_WHITE);
    DrawLine(0, 0, 0, ScreenHeight() - 1, FG_WHITE);
    DrawLine(ScreenWidth() - 1, 0, ScreenWidth() - 1, ScreenHeight() - 1);

    std::stringstream ss;
    ss << "ROUND " << nRound;

    DrawString(4, 4, ss.str());

    ss.str("");
    ss << "SCORE " << nScore;

    DrawString(ScreenWidth() - 4 - 8 * (int)ss.str().length(), 4, ss.str());

    DrawFilledRectangle((int)sPaddle.x, sPaddle.y, (int)sPaddle.x + sPaddle.w,
                        sPaddle.y + sPaddle.h);

    for (auto &brick : aBricks) {

      if (brick.active) {

        DrawFilledRectangle(brick.x, brick.y, brick.x + brick.w,
                            brick.y + brick.h, brick.color);
      }
    }

    for (int i = 0; i < nBalls; i++) {

      DrawFilledCircle(70 + i * 2 * (sBall.r + 1), 7, sBall.r);
    }

    for (int i = nBalls; i < 3; i++) {

      DrawCircle(70 + i * 2 * (sBall.r + 1), 7, sBall.r);
    }

    DrawFilledCircle((int)sBall.x, (int)sBall.y, sBall.r);

    if (bPaused) {

      ss.str("-PAUSED-");

      DrawString((ScreenWidth() - 8 * (int)ss.str().length()) / 2,
                 (ScreenHeight() - 8) / 2, ss.str(), FG_BROWN);
    }

    if (!bGameMode) {
      ss.str("-PRESS SPACE-");

      DrawString((ScreenWidth() - 8 * (int)ss.str().length()) / 2,
                 (ScreenHeight() - 8) / 2, ss.str(), FG_BROWN);
    }

    if (bMouse) {

      DrawString(4 + 90, 4, "M", FG_YELLOW);
    }
  }

  void InitBall() {

    sBall.x = ScreenWidth() / 2;
    sBall.y = 2 * ScreenHeight() / 3;
    sBall.dx = (((float)rand() / RAND_MAX) > 0.5 ? -1.0f : 1.0f) *
               (2.5f + 10.0f * ((float)rand() / RAND_MAX));
    sBall.dy = -sqrtf(160.0f - sBall.dx * sBall.dx);
  }

  void InitPaddle() {

    sPaddle.x = (ScreenWidth() - sPaddle.w) / 2.0;
    sPaddle.y = (ScreenHeight() - 25);
    sPaddle.w = 30.0f;
  }

  void InitBricks() {

    std::array<int, 6> colors = {FG_BLACK, FG_RED,  FG_YELLOW,
                                 FG_CYAN,  FG_LIME, FG_GREEN};

    int i = 0;
    int j = 0;
    for (auto &brick : aBricks) {
      brick.w = 25;
      brick.h = 10;
      brick.x = 12 + ((brick.w + 5) * i++);
      brick.y = 30 + (brick.h + 5) * j;
      brick.color = colors[j];
      brick.active = true;
      if (i == 6) {
        i = 0;
        ++j;
      }
      brick.points = 6 - j;
    }
    nActive = aBricks.size();
  }

  cb::SampledAudio Audio;
  std::array<sBrick, 36> aBricks;

  struct {
    float x;
    float y;
    float w;
    float h = 3.0f;
  } sPaddle;

  struct {
    float x;
    float y;
    float r = 2.0f;
    float dx;
    float dy;
  } sBall;

  int nScore;
  int nPrevScore;
  int nRound;
  int nBalls;
  int nActive;

  int GameOverSample = 0;
  int LostSample = 0;
  int LevelUpSample = 0;
  int PaddleSample = 0;
  int BreakSample = 0;

  bool bFinished = false;
  bool bPaused = false;
  bool bGameMode = false;
  bool bMouse = true;
};

#endif // CBGLGFX_BREAKOUT_H_
