/**
 *  @file   Frogger.h
 *  @brief  Frogger in CBGLGFX
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGFX_FROGGER_H_
#define CBGLGFX_FROGGER_H_

#include "../GLGFX.h"
#include "../SampledAudio.h"
#include "../Sprite.h"

#include <cstring>

extern "C" size_t music_s;
extern "C" size_t music_sz;
extern "C" const char music_z[];

extern "C" size_t hop_s;
extern "C" size_t hop_sz;
extern "C" const char hop_z[];

extern "C" size_t squash_s;
extern "C" size_t squash_sz;
extern "C" const char squash_z[];

extern "C" size_t plunk_s;
extern "C" size_t plunk_sz;
extern "C" const char plunk_z[];

extern "C" size_t timeout_s;
extern "C" size_t timeout_sz;
extern "C" const char timeout_z[];

extern "C" size_t winner_s;
extern "C" size_t winner_sz;
extern "C" const char winner_z[];

class Frogger : public cb::GLGFX {

public:
  Frogger() { sTitle = "Frogger"; }

private:
  bool OnUserCreate() final {

    nMusicID = audio.z_Load(music_z, music_sz, music_s);
    nHopID = audio.z_Load(hop_z, hop_sz, hop_s);
    nSquashID = audio.z_Load(squash_z, squash_sz, squash_s);
    nPlunkID = audio.z_Load(plunk_z, plunk_sz, plunk_s);
    nTimeoutID = audio.z_Load(timeout_z, timeout_sz, timeout_s);
    nWinnerID = audio.z_Load(winner_z, winner_sz, winner_s);

    audio.SetAudioSamplerate(22050);
    audio.SetAudioStereo(1);
    audio.SetAudioChannels(64);
    audio.SetBitsPerChannel(8);
    audio.SetVolume(25);
    audio.Start();

    audio.Play(nMusicID, true);

    bDanger = new bool[ScreenWidth() * ScreenHeight()];
    std::memset(bDanger, 0, ScreenWidth() * ScreenHeight() * sizeof(bool));

    sprBus.ReadolcSprite(L"gfx/bus.sprite");
    sprCar1.ReadolcSprite(L"gfx/car1.sprite");
    sprCar2.ReadolcSprite(L"gfx/car2.sprite");
    sprFrog.ReadolcSprite(L"gfx/frog.sprite");
    sprHome.ReadolcSprite(L"gfx/home.sprite");
    sprLog.ReadolcSprite(L"gfx/log.sprite");
    sprPavement.ReadolcSprite(L"gfx/pavement.sprite");
    sprWall.ReadolcSprite(L"gfx/wall.sprite");
    sprWater.ReadolcSprite(L"gfx/water.sprite");

    return true;
  }

  void OnUserDestroy() final { delete bDanger; }

  bool OnUserUpdate(float fElapsedTime) final {

    if (!bGameOver)
      fTotalTime += fElapsedTime;

    Input();

    Logic(fElapsedTime);

    Draw();

    return !bFinished;
  }

  void Input() {

    if (KeyUp('q'))
      bFinished = true;

    if ((bGameOver || bWinner) && KeyUp(' ')) {
      fFrogX = 8.0f;
      fFrogY = 9.0f;
      fCountdown = 16.0f;
      bGameOver = false;
      bWinner = false;
    }

    if (!(bGameOver || bWinner)) {
      if (KeySpecialDown(GLUT_KEY_UP)) {
        fFrogY -= 1.0f;
        audio.Play(nHopID);
      }
      if (KeySpecialDown(GLUT_KEY_DOWN)) {
        fFrogY += 1.0f;
        audio.Play(nHopID);
      }
      if (KeySpecialDown(GLUT_KEY_LEFT)) {
        fFrogX -= 1.0f;
        audio.Play(nHopID);
      }
      if (KeySpecialDown(GLUT_KEY_RIGHT)) {
        fFrogX += 1.0f;
        audio.Play(nHopID);
      }

      if (fFrogX < 0)
        fFrogX = 0.0f;
      if (fFrogX > static_cast<float>(ScreenWidth() / nCellSize) - 1.0f)
        fFrogX = static_cast<float>(ScreenWidth() / nCellSize) - 1.0f;
      if (fFrogY < 0)
        fFrogY = 0.0f;
      if (fFrogY > static_cast<float>(ScreenHeight() / nCellSize) - 1.0f)
        fFrogY = static_cast<float>(ScreenHeight() / nCellSize) - 1.0f;
    }
  }

  void Draw() {

    int x = -1, y = 0;
    for (auto lane : vecLanes) {

      int nStartPos = (int)(fTotalTime * lane.first) % 64;
      if (nStartPos < 0)
        nStartPos = 64 - (std::abs(nStartPos) % 64);
      int nCellOffset =
          (int)((float)nCellSize * fTotalTime * lane.first) % nCellSize;

      for (int i = 0; i < (ScreenWidth() / nCellSize) + 2; i++) {

        char graphic = lane.second[(nStartPos + i) % 64];
        int x0 = (x + i) * nCellSize - nCellOffset;
        int y0 = y * nCellSize;

        switch (graphic) {

        case L',':
          DrawSprite(sprWater, x0, y0, 0, 0, 8, 8);
          break;

        case L'j':
          DrawSprite(sprLog, x0, y0, 0, 0, 8, 8);
          break;
        case L'l':
          DrawSprite(sprLog, x0, y0, 8, 0, 8, 8);
          break;
        case L'k':
          DrawSprite(sprLog, x0, y0, 16, 0, 8, 8);
          break;

        case L'a':
          DrawSprite(sprBus, x0, y0, 0, 0, 8, 8);
          break;
        case L's':
          DrawSprite(sprBus, x0, y0, 8, 0, 8, 8);
          break;
        case L'd':
          DrawSprite(sprBus, x0, y0, 16, 0, 8, 8);
          break;
        case L'f':
          DrawSprite(sprBus, x0, y0, 24, 0, 8, 8);
          break;

        case L'z':
          DrawSprite(sprCar1, x0, y0, 0, 0, 8, 8);
          break;
        case L'x':
          DrawSprite(sprCar1, x0, y0, 8, 0, 8, 8);
          break;

        case L't':
          DrawSprite(sprCar2, x0, y0, 0, 0, 8, 8);
          break;
        case L'y':
          DrawSprite(sprCar2, x0, y0, 8, 0, 8, 8);
          break;

        case L'p':
          DrawSprite(sprPavement, x0, y0, 0, 0, 8, 8);
          break;
        case L'h':
          DrawSprite(sprHome, x0, y0, 0, 0, 8, 8);
          break;
        case L'w':
          DrawSprite(sprWall, x0, y0, 0, 0, 8, 8);
          break;

        case L'.':
          DrawFilledRectangle(x0, y0, (x + i + 1) * nCellSize - nCellOffset,
                              (y + 1) * nCellSize, FG_BLACK);

        default:
          break;
        }
      }
      ++y;
    }

    DrawString(1, ScreenHeight() - 8, std::to_string((int)fCountdown), FG_RED);

    DrawSprite(sprFrog, fFrogX * nCellSize, fFrogY * nCellSize);

    if (bGameOver)
      DrawString((ScreenWidth() - 80) / 2, (ScreenHeight() - 16) / 2,
                 "GAME OVER!", FG_RED);

    if (bWinner)
      DrawString((ScreenWidth() - 80) / 2, (ScreenHeight() - 16) / 2,
                 "! WINNER !", FG_RED);

    if (bGameOver || bWinner)
      DrawString((ScreenWidth() - 104) / 2, (ScreenHeight() + 2) / 2,
                 "press <space>", FG_WHITE);
  }

  void Logic(float &fElapsedTime) {

    int x = -1, y = 0;
    for (auto lane : vecLanes) {

      int nStartPos = (int)(fTotalTime * lane.first) % 64;
      if (nStartPos < 0)
        nStartPos = 64 - (std::abs(nStartPos) % 64);
      int nCellOffset =
          (int)((float)nCellSize * fTotalTime * lane.first) % nCellSize;

      for (int i = 0; i < (ScreenWidth() / nCellSize) + 2; i++) {

        char graphic = lane.second[(nStartPos + i) % 64];

        for (int j = (x + i) * nCellSize - nCellOffset;
             j < (x + i + 1) * nCellSize - nCellOffset; j++) {
          for (int k = y * nCellSize; k < (y + 1) * nCellSize; k++) {
            if (j >= 0 && j < ScreenWidth() && k >= 0 && k < ScreenHeight())
              bDanger[j + ScreenWidth() * k] =
                  !(graphic == L'.' || graphic == L'j' || graphic == L'l' ||
                    graphic == L'k' || graphic == L'p' || graphic == 'h');
          }
        }
      }
      ++y;
    }

    if (fFrogY <= 3 && !bGameOver)
      fFrogX -= fElapsedTime * vecLanes[(int)fFrogY].first;

    if (!(bGameOver || bWinner) &&
        (bDanger[(int)(fFrogY * nCellSize + 1) * ScreenWidth() +
                 (int)(fFrogX * nCellSize + 1)] || // tl
         bDanger[(int)(fFrogY * nCellSize + 1) * ScreenWidth() +
                 (int)((fFrogX + 1) * nCellSize - 1)] || // tr
         bDanger[(int)((fFrogY + 1) * nCellSize - 1) * ScreenWidth() +
                 (int)(fFrogX * nCellSize + 1)] || // bl
         bDanger[(int)((fFrogY + 1) * nCellSize - 1) * ScreenWidth() +
                 (int)((fFrogX + 1) * nCellSize - 1)])) { // br
      if (fFrogY <= 3)
        audio.Play(nPlunkID);
      else
        audio.Play(nSquashID);
      bGameOver = true;
    }

    if (!(bWinner || bGameOver) && fFrogY < 1 &&
        !bDanger[(int)(fFrogX * nCellSize)]) {
      audio.Play(nWinnerID);
      bWinner = true;
    }

    if (!(bGameOver || bWinner))
      fCountdown -= fElapsedTime;

    if (fCountdown < 0.0f) {
      fCountdown = 0.0f;
      audio.Play(nTimeoutID);
      bGameOver = true;
    }
  }

  // 10x64 game space
  std::vector<std::pair<float, std::wstring>> vecLanes = {
      {0.0f,
       L"wwwhhwwwhhwwwhhwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"},
      {-3.0f,
       L",,,jllk,,jllllk,,,,,,,jllk,,,,,jk,,,jlllk,,,,jllllk,,,,jlllk,,,,"},
      {3.0f,
       L",,,,jllk,,,,,jllk,,,,jllk,,,,,,,,,jllk,,,,,jk,,,,,,jllllk,,,,,,,"},
      {2.0f,
       L",,jlk,,,,,jlk,,,,,jk,,,,,jlk,,,jlk,,,,jk,,,,jllk,,,,jk,,,,,,jk,,"},
      {0.0f, L"ppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp"
             L"p"}, // pavement
      {-3.0f,
       L"....asdf.......asdf....asdf..........asdf........asdf....asdf..."},
      {3.0f, L".....ty..ty....ty....ty.....ty........ty..ty.ty......ty......."
             L"ty"}, // bus
      {-4.0f, L"..zx.....zx.........zx..zx........zx...zx...zx....zx...zx...zx."
              L"."}, // car2
      {2.0f, L"..ty.....ty.......ty.....ty......ty..ty.ty.......ty....ty......"
             L"."}, // car1
      {0.0f, L"ppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp"
             L"p"}}; // pavement

  bool *bDanger = nullptr;

  bool bFinished = false;

  bool bGameOver = false;

  bool bWinner = false;

  float fTotalTime = 0.0f;

  float fCountdown = 16.0f;

  float fFrogX = 8.0f;

  float fFrogY = 9.0f;

  int nCellSize = 8;

  cb::Sprite sprBus, sprCar1, sprCar2, sprFrog, sprHome, sprLog, sprPavement,
      sprWall, sprWater;

  cb::SampledAudio audio;

  int nMusicID{};

  int nHopID{};

  int nSquashID{};

  int nPlunkID{};

  int nTimeoutID{};

  int nWinnerID{};
};

#endif // CBGLGFX_FROGGER_H_
