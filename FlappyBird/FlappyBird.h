/**
 *  @file   FlappyBird.h
 *  @brief  Flappy Bird in GLGFX
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGFX_FLAPPYBIRD_H_
#define CBGLGFX_FLAPPYBIRD_H_

#include "../GLGFX.h"
#include "../SampledAudio.h"
#include "../Sprite.h"

#include <chrono>
#include <iomanip>
#include <random>
#include <sstream>

class FlappyBird : public cb::GLGFX {

public:
  FlappyBird() {
    sTitle = "Flappy BirdSprite";
    bShowFPS = false;
  }

private:
  bool OnUserCreate() final {

    better_rand.seed(
        std::chrono::system_clock::now().time_since_epoch().count());

    vField.insert(vField.begin(), 1 + ScreenWidth() / (nGapHeight + nPipeWidth),
                  0);

    CityBitmap = ReadBitmap(L"gfx/city.bmp");

    BirdSprite.Read(L"gfx/birds.sprite");

    nBirdWidth = BirdSprite.SpriteWidth() / 3;

    nBirdHeight = BirdSprite.SpriteHeight();

    PipeSprite.Read(L"gfx/pipe.sprite");

    nPipeWidth = PipeSprite.SpriteWidth() / 2;

    DieSoundSample = Audio.LoadFromFile("sfx/die.raw");

    HitSoundSample = Audio.LoadFromFile("sfx/hit.raw");

    PointSoundSample = Audio.LoadFromFile("sfx/point.raw");

    // SwooshingSoundSample = Audio.LoadFromFile( "swooshing.raw" );

    WingSoundSample = Audio.LoadFromFile("sfx/wing.raw");

    Reset();

    Audio.SetAudioSamplerate(22050);
    Audio.SetAudioStereo(1);
    Audio.SetAudioChannels(64);
    Audio.SetBitsPerChannel(8);
    Audio.SetVolume(25);
    Audio.Start();

    std::ifstream ifstr(std::filesystem::path(L".flappybird"));
    if (ifstr.good()) {
      ifstr >> nBestScore;
      ifstr.close();
    } else
      nBestScore = 0.0f;

    return true;
  }

  void OnUserDestroy() final { FreeBitmap(CityBitmap); }

  bool OnUserUpdate(float fElapsedTime) final {

    fFrameTime = fElapsedTime;

    Input();

    Logic();

    Draw();

    return !bFinished;
  }

  void Input() {

    if (KeyUp('q'))
      bFinished = true;
    if (KeyDown(' ')) {
      if (bGameOver)
        Reset();
      else if (fBirdSpeed >= fGravity / 10.0f) {
        Audio.Play(WingSoundSample);
        fPlayerAcceleration = 0.0f;
        fBirdSpeed = -fGravity / 4.0f;
      }
    } else
      fPlayerAcceleration += fGravity * fFrameTime;
  }

  void Logic() {

    if (bGameOver)
      return;

    fGameX -= fFrameTime * fGameSpeed;

    if ((int)fGameX < -(nPipeWidth + nGapHeight)) {
      vField.erase(vField.begin());
      vField.push_back(
          (better_rand() % (nFloorY - nGapWidth - 2 * nPipeMinHeight)) +
          nPipeMinHeight);
      fGameX += (float)(nPipeWidth + nGapHeight);
      bPipeCleared = false;
    } else if (!bPipeCleared &&
               nBirdX > (nGapHeight + (int)fGameX + nPipeWidth)) {
      if (++nScore % 10 == 0)
        fGameSpeed += 10.0f;
      bPipeCleared = true;
      Audio.Play(PointSoundSample);
    }

    if (fPlayerAcceleration > fGravity)
      fPlayerAcceleration = fGravity;

    fBirdSpeed += fPlayerAcceleration * fFrameTime;
    fBirdY += fBirdSpeed * fFrameTime;

    if (fBirdY < 0)
      fBirdY = 0.0f;
    else if (fBirdY > (float)(nFloorY - nBirdHeight)) {
      Audio.Play(DieSoundSample);
      fBirdY = (float)(nFloorY - nBirdHeight);
      bGameOver = true;
    }

    if ((nBirdX + nBirdWidth) > (nGapHeight + (int)fGameX) &&
        ((nBirdX + nBirdWidth) < (nGapHeight + (int)fGameX + 5))) {

      if (fBirdY < (float)vField.front()) {
        Audio.Play(HitSoundSample);
        fGameX = (float)(nBirdX + nBirdWidth - nGapHeight);
        bGameOver = true;
      } else if ((fBirdY + (float)nBirdWidth) >
                 (float)(vField.front() + nGapWidth)) {
        Audio.Play(HitSoundSample);
        fGameX = (float)(nBirdX + nBirdWidth - nGapHeight);
        bGameOver = true;
      }
    } else if ((nBirdX + nBirdWidth) > (nGapHeight + (int)fGameX) &&
               nBirdX < (nGapHeight + (int)fGameX + nPipeWidth)) {

      if (fBirdY < (float)vField.front()) {
        Audio.Play(HitSoundSample);
        fBirdY = vField.front();
        bGameOver = true;
      } else if ((fBirdY + (float)nBirdHeight) >
                 (float)(vField.front() + nGapWidth)) {
        Audio.Play(HitSoundSample);
        fBirdY = (float)(vField.front() + nGapWidth - nBirdHeight);
        bGameOver = true;
      }
    }

    if (bGameOver && nScore > nBestScore) {
      nBestScore = nScore;
      std::ofstream ofstr(std::filesystem::path(L".flappybird"));
      if (ofstr.good()) {
        ofstr << nBestScore;
        ofstr.close();
      }
    }
  }

  void Draw() {

    if (!bGameOver)
      fBackgroundX += fFrameTime * fGameSpeed / 2.0f;

    if ((int)fBackgroundX > CityBitmap->width)
      fBackgroundX = 0.0f;

    int nWidth = ScreenWidth();

    if (((int)fBackgroundX + nWidth) > CityBitmap->width)
      nWidth = CityBitmap->width - (int)fBackgroundX;

    DrawBitmap(*CityBitmap, 0, 0, (int)fBackgroundX, 0, nWidth, ScreenHeight());

    if (nWidth < ScreenWidth())
      DrawBitmap(*CityBitmap, nWidth, 0, 0, 0, ScreenWidth() - nWidth,
                 ScreenHeight());

    int i = 0;

    for (int nField : vField) {

      DrawSprite(PipeSprite,
                 (i + 1) * nGapHeight + i * nPipeWidth + (int)fGameX, 0, 0,
                 PipeSprite.SpriteHeight() - nField, nPipeWidth, nField);

      DrawSprite(PipeSprite,
                 (i + 1) * nGapHeight + i * nPipeWidth + (int)fGameX,
                 nField + nGapWidth, nPipeWidth, 0, nPipeWidth,
                 nFloorY - nField - nGapWidth);

      ++i;
    }

    if (fBirdSpeed < 0)
      nBirdFrame = 2;
    else
      nBirdFrame = 0;

    DrawSprite(BirdSprite, nBirdX, (int)fBirdY, nBirdWidth * nBirdFrame, 0,
               nBirdWidth, nBirdHeight);

    std::stringstream ss;

    ss << "SCORE: " << std::setfill('0') << std::setw(3) << nScore;

    DrawString(4, ScreenHeight() - 14, ss.str(), FG_BROWN);

    ss.str("");

    ss << "BEST: " << std::setfill('0') << std::setw(3) << nBestScore;

    DrawString(ScreenWidth() - 76, ScreenHeight() - 14, ss.str(), FG_BROWN);

    if (bGameOver)
      DrawString((ScreenWidth() - 72) / 2, (ScreenHeight() - 8) / 2,
                 "GAME OVER", FG_RED);
  }

  void Reset() {

    bGameOver = false;

    fBirdY = 0.0;

    fBirdSpeed = 0.0f;

    fPlayerAcceleration = 0.0f;

    fGameX = 0.0f;

    nScore = 0;

    fGameSpeed = 80.0f;

    fBackgroundX = 0.0f;

    nBirdFrame = 1;

    for (int &nField : vField)
      nField =
          ((int)better_rand() % (nFloorY - nGapWidth - 2 * nPipeMinHeight)) +
          nPipeMinHeight;

    fBirdY = (float)vField.front();
  }

  bool bFinished = false;

  cb::SampledAudio Audio;

  static constexpr float fGravity = 250.0f;

  static constexpr int nFloorY = 178;

  static constexpr int nBirdX = 25;

  static constexpr int nPipeMinHeight = 13;

  static constexpr int nGapWidth = 74;

  static constexpr int nGapHeight = 137;

  float fPlayerAcceleration = 0.0f;

  int nPipeWidth = 0;

  float fBirdSpeed = 0.0f;

  float fBirdY = 0.0f;

  float fFrameTime = 0.0f;

  int nScore = 0.0f;

  int nBestScore = 0.0;

  bool bGameOver = false;

  float fGameSpeed = 0.0f;

  float fGameX = 0.0f;

  bool bPipeCleared = false;

  std::minstd_rand better_rand;

  std::vector<int> vField;

  Bitmap *CityBitmap = nullptr;

  float fBackgroundX = 0.0f;

  cb::Sprite BirdSprite;

  int nBirdWidth = 0;

  int nBirdHeight = 0;

  int nBirdFrame = 1;

  cb::Sprite PipeSprite;

  int DieSoundSample = -1;

  int HitSoundSample = -1;

  int PointSoundSample = -1;

  // int SwooshingSoundSample = -1;

  int WingSoundSample = -1;
};

#endif // CBGLGFX_FLAPPYBIRD_H_
