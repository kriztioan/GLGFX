/**
 *  @file   Destroyer.h
 *  @brief  Destroyer in GLGFX
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGFX_DESTROYER_H_
#define CBGLGFX_DESTROYER_H_

#include "../GLGFX.h"
#include "../SampledAudio.h"

#include <chrono>
#include <iomanip>
#include <random>
#include <sstream>

class Destroyer : public cb::GLGFX {

public:
  Destroyer() {
    sTitle = "Destroyer";
    bShowFPS = false;
  }

private:
  bool OnUserCreate() final {

    better_rand.seed(
        std::chrono::system_clock::now().time_since_epoch().count());

    fDestroyerVelocity = -75.0f;

    DestroyerSprite.Read(L"gfx/destroyer.sprite");

    nDestroyerWidth = DestroyerSprite.SpriteWidth();

    nDestroyerHeight = DestroyerSprite.SpriteHeight() / 2;

    fDestroyerX = (float)(ScreenWidth() - nDestroyerWidth) / 2.0f;

    SubmarineSprite.Read(L"gfx/submarine.sprite");

    nSubmarineWidth = SubmarineSprite.SpriteWidth() / 5;

    nSubmarineHeight = SubmarineSprite.SpriteHeight() / 2;

    nLanes = (ScreenHeight() - (3 * nDestroyerHeight / 2) - nDestroyerY) /
             nSubmarineHeight;

    DepthChargeSprite.Read(L"gfx/barrel.sprite");

    nDepthChargeWidth = DepthChargeSprite.SpriteWidth();

    nDepthChargeHeight = DepthChargeSprite.SpriteHeight();

    nDepthCharges = 3;

    nBonusNeeded = 50;

    DepthChargeSample = Audio.LoadFromFile("sfx/charge.raw");

    PingSample = Audio.LoadFromFile("sfx/ping.raw");

    ReleaseSample = Audio.LoadFromFile("sfx/release.raw");

    GameOverSample = Audio.LoadFromFile("sfx/gameover.raw");

    BonusSample = Audio.LoadFromFile("sfx/bonus.raw");

    DepthChargeLostSample = Audio.LoadFromFile("sfx/lost.raw");

    Audio.SetAudioSamplerate(22050);
    Audio.SetAudioStereo(1);
    Audio.SetAudioChannels(64);
    Audio.SetBitsPerChannel(8);
    Audio.SetVolume(25);
    Audio.Start();

    std::ifstream ifstr(std::filesystem::path(L".destroyer"));
    if (ifstr.good()) {
      ifstr >> nBestHits;
      ifstr.close();
    } else
      nBestHits = 0.0f;

    return true;
  }

  void Reset() {

    vSubmarines.clear();

    vDepthCharges.clear();

    nHits = 0;

    nBonusNeeded = 50;

    fPingTime = 0.0f;

    fDestroyerX = (float)(ScreenWidth() - nDestroyerWidth) / 2.0f;

    nDepthCharges = 3;

    bGameOver = false;
  }

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
    if (KeyUp('r'))
      Reset();
    if (KeyDown(' ')) {
      if (bGameOver)
        Reset();
      else if (nDepthCharges > 0) {
        Audio.Play(ReleaseSample);
        Coordinates c = {fDestroyerX + (float)nDestroyerWidth / 2.0f,
                         (float)(nDestroyerY + nDestroyerHeight),
                         0.0f,
                         fDepthChargeVelocity,
                         0,
                         0.0f,
                         false,
                         false};
        vDepthCharges.emplace_back(c);
        --nDepthCharges;
      }
    }
  }

  void Logic() {

    if (bGameOver)
      return;

    fPingTime += fFrameTime / 2.0f;

    fDestroyerX += (fDestroyerVelocity * fFrameTime);

    if (fDestroyerX < 0.0f) {
      fDestroyerX = 0.0f;
      uint32_t i =
          (*(uint32_t *)&fDestroyerVelocity) ^ 0x80000000; // fast negate
      std::memcpy(&fDestroyerVelocity, &i, sizeof(float));
    } else if ((int)fDestroyerX >= (ScreenWidth() - nDestroyerWidth)) {
      fDestroyerX = (float)(ScreenWidth() - nDestroyerWidth - 1);
      uint32_t i =
          (*(uint32_t *)&fDestroyerVelocity) ^ 0x80000000; // fast negate
      std::memcpy(&fDestroyerVelocity, &i, sizeof(float));
    }

    for (auto &DepthCharge : vDepthCharges) {
      DepthCharge.y += DepthCharge.dy * fFrameTime;
      if ((int)DepthCharge.y > ScreenHeight()) {
        Audio.Play(DepthChargeLostSample);
        DepthCharge.destroy = true;
      }
    }

    auto vDestroy =
        std::remove_if(vDepthCharges.begin(), vDepthCharges.end(),
                       [](const Coordinates &c) -> bool { return c.destroy; });

    vDepthCharges.erase(vDestroy, vDepthCharges.end());

    for (auto &Submarine : vSubmarines) {
      if (Submarine.hit)
        Submarine.frame += 20.0f * fFrameTime;
      Submarine.x += Submarine.dx * fFrameTime;
      if ((Submarine.x < (float)-nSubmarineWidth) ||
          Submarine.x >= (float)ScreenWidth() || Submarine.frame >= 5.0f)
        Submarine.destroy = true;
    }

    vDestroy =
        std::remove_if(vSubmarines.begin(), vSubmarines.end(),
                       [](const Coordinates &c) -> bool { return c.destroy; });

    vSubmarines.erase(vDestroy, vSubmarines.end());

    while (vSubmarines.size() < 3) {
      float direction = 2.0f * (float)(better_rand() % 2) - 1.0f;
      float x = direction > 0.0f ? (float)-nSubmarineWidth
                                 : (float)ScreenWidth() - 1.0f;
      int lane = static_cast<int>(better_rand()) % nLanes;
      auto y = static_cast<float>(nDestroyerY + (3 * nDestroyerHeight / 2) +
                                  lane * nSubmarineHeight);
      float dx = direction * (10.0f + (float)(better_rand() % 40));
      Coordinates c = {x, y, dx, 0.0f, lane, 0.0f, false, false};
      vSubmarines.emplace_back(c);
    }

    for (auto &DepthCharge : vDepthCharges) {
      for (auto &Submarine : vSubmarines) {
        if (Submarine.hit)
          continue;
        if ((DepthCharge.x + (float)nDepthChargeWidth) > Submarine.x &&
            DepthCharge.x < (Submarine.x + (float)nSubmarineWidth) &&
            DepthCharge.y + (float)nDepthChargeHeight > Submarine.y &&
            DepthCharge.y < (Submarine.y + (float)nSubmarineHeight)) {
          Audio.Play(DepthChargeSample);
          DepthCharge.destroy = Submarine.hit = true;
          Submarine.frame = 1.0f;
          nHits += 1 + Submarine.lane;
          if (nHits >= nBonusNeeded) {
            Audio.Play(BonusSample);
            ++nDepthCharges;
            nBonusNeeded += 50;
          }
          ++nDepthCharges;
        }
      }
    }

    if (nDepthCharges == 0 && vDepthCharges.empty()) {
      if (nHits > nBestHits) {
        nBestHits = nHits;
        std::ofstream ofstr(std::filesystem::path(L".destroyer"));
        if (ofstr.good()) {
          ofstr << nBestHits;
          ofstr.close();
        }
      }
      Audio.Play(GameOverSample);
      bGameOver = true;
    }
  }

  void Draw() {

    if (fPingTime > fPingTimeTrigger) {
      Audio.Play(PingSample);
      fPingTime = 0.0f;
      fPingTimeTrigger = (float)(better_rand() % 8);
    }

    DrawFilledRectangle(0, 0, ScreenWidth() - 1, nDestroyerY + nDestroyerHeight,
                        FG_BLUE);

    DrawFilledRectangle(0, nDestroyerY + nDestroyerHeight, ScreenWidth() - 1,
                        ScreenHeight() - 1, FG_NAVY);

    for (int i = 0; i < nLanes; i++) {

      int y =
          nDestroyerY + (3 * nDestroyerHeight / 2) + (i + 1) * nSubmarineHeight;

      DrawString(4, y - 4, std::to_string(i + 1), FG_GREY2);

      DrawLine(18, y, ScreenWidth() - 18, y, FG_GREY2);
    }

    DrawSprite(DestroyerSprite, (int)fDestroyerX, nDestroyerY, 0,
               fDestroyerVelocity > 0.0f ? 0 : nDestroyerHeight,
               nDestroyerWidth, nDestroyerHeight);

    for (auto Submarine : vSubmarines) {
      DrawSprite(SubmarineSprite, (int)Submarine.x, (int)Submarine.y,
                 ((int)Submarine.frame % 5) * nSubmarineWidth,
                 Submarine.dx > 0 ? 0 : nSubmarineHeight, nSubmarineWidth,
                 nSubmarineHeight);

      if (Submarine.hit) {

        std::stringstream ss;

        ss << '+' << (Submarine.lane + 1);

        DrawString((int)Submarine.x + nSubmarineWidth / 2 - 8,
                   (int)(Submarine.y - 2.0f * Submarine.frame), ss.str(),
                   FG_RED);
      }
    }

    for (auto DepthCharge : vDepthCharges)
      DrawSprite(DepthChargeSprite, (int)DepthCharge.x, (int)DepthCharge.y);

    std::stringstream ss;

    ss << "CHARGES: " << nDepthCharges;

    DrawString((ScreenWidth() - 8 * (int)ss.str().length()) / 2, 4, ss.str(),
               FG_BROWN);

    ss.str("");

    ss << "HITS: " << std::setfill('0') << std::setw(3) << nHits;

    DrawString(4, 4, ss.str(), FG_MAROON);

    ss.str("");

    ss << "BEST: " << std::setfill('0') << std::setw(3) << nBestHits;

    DrawString(ScreenWidth() - 76, 4, ss.str(), FG_MAROON);

    if (bGameOver)
      DrawString((ScreenWidth() - 72) / 2, (ScreenHeight() - 8) / 2,
                 "GAME OVER", FG_RED);
  }

  struct Coordinates {
    float x;
    float y;
    float dx;
    float dy;
    int lane;
    float frame;
    bool destroy;
    bool hit;
  };

  bool bFinished = false;

  float fDestroyerVelocity = 0.0f;

  int nDestroyerWidth = 0;

  int nDestroyerHeight = 0;

  float fDestroyerX = 0.0f;

  static constexpr int nDestroyerY = 45;

  static constexpr float fDepthChargeVelocity = 25.0f;

  int nSubmarineWidth = 0;

  int nSubmarineHeight = 0;

  int nLanes = 0;

  int nDepthChargeWidth = 0;

  int nDepthChargeHeight = 0;

  float fPingTime = 0.0f;

  float fPingTimeTrigger = 0.0f;

  float fFrameTime = 0.0f;

  int nBestHits = 0;

  int nHits = 0;

  int nDepthCharges = 0;

  int nBonusNeeded = 0;

  std::vector<Coordinates> vSubmarines;

  std::vector<Coordinates> vDepthCharges;

  std::minstd_rand better_rand;

  bool bGameOver = false;

  cb::Sprite SubmarineSprite;

  cb::Sprite DestroyerSprite;

  cb::Sprite DepthChargeSprite;

  cb::SampledAudio Audio;

  int ReleaseSample = 0;

  int DepthChargeSample = 0;

  int PingSample = 0;

  int GameOverSample = 0;

  int BonusSample = 0;

  int DepthChargeLostSample = 0;
};

#endif // CBGLGFX_DESTROYER_H_
