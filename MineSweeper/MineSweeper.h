/**
 *  @file   MineSweeper.h
 *  @brief  Mine Sweeper in CBGLGFX
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/
#ifndef CBGLGFX_MINESWEEPER_H
#define CBGLGFX_MINESWEEPER_H

#include "../GLGFX.h"
#include "../SampledAudio.h"
#include "../Sprite.h"

#include <chrono>
#include <iomanip>
#include <numeric>
#include <random>
#include <sstream>

class MineSweeper : public cb::GLGFX {

public:
  MineSweeper() {
    sTitle = "Mine Sweeper";
    bShowFPS = false;
  }

private:
  bool OnUserCreate() final {

    nCols = ScreenWidth() / nCellSize;
    nRows = (ScreenHeight() - nFieldOffsetY) / nCellSize;

    Tiles = ReadBitmap(L"gfx/tiles.bmp");

    nTickID = audio.LoadFromFile("sfx/tick.raw");
    nLoseID = audio.LoadFromFile("sfx/lose.raw");
    nWinID = audio.LoadFromFile("sfx/win.raw");

    bField = new bool[nRows * nCols];
    nField = new int[nRows * nCols];
    cPlayer = new char[nRows * nCols];

    better_rand.seed(
        std::chrono::system_clock::now().time_since_epoch().count());

    Reset();

    audio.SetAudioSamplerate(22050);
    audio.SetAudioStereo(1);
    audio.SetAudioChannels(64);
    audio.SetBitsPerChannel(8);
    audio.SetVolume(25);
    audio.Start();

    std::ifstream ifstr(std::filesystem::path(L".minesweeper"));
    if (ifstr.good()) {
      ifstr >> fBestTime;
      ifstr.close();
    } else
      fBestTime = 999.0f;

    return true;
  }

  void OnUserDestroy() final {

    delete[] bField;
    delete[] nField;
    delete[] cPlayer;
    FreeBitmap(Tiles);
  }

  bool OnUserUpdate(float fElapsedTime) final {

    if (GameState == GameStateRunning) {
      fTimer += fElapsedTime;
      if (fTimer > 999.0f)
        fTimer = 999.0f;
    }

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
    if (GameState == GameStateRunning) {
      if (MouseUp(GLUT_LEFT_BUTTON, nMouseX, nMouseY) &&
          nMouseY > nFieldOffsetY) {
        audio.Play(nTickID);
        nMouseX /= nCellSize;
        nMouseY -= nFieldOffsetY;
        nMouseY /= nCellSize;
        if (nMouseX >= 0 && nMouseX < nCols && nMouseY >= 0 && nMouseY < nRows)
          cPlayer[nMouseX + nMouseY * nCols] = 1;
      }
      if (MouseUp(GLUT_RIGHT_BUTTON, nMouseX, nMouseY) &&
          nMouseY > nFieldOffsetY) {
        audio.Play(nTickID);
        nMouseX /= nCellSize;
        nMouseY -= nFieldOffsetY;
        nMouseY /= nCellSize;
        if (nMouseX >= 0 && nMouseX < nCols && nMouseY >= 0 &&
            nMouseY < nRows && cPlayer[nMouseX + nMouseY * nCols] != 1)
          cPlayer[nMouseX + nMouseY * nCols] =
              cPlayer[nMouseX + nMouseY * nCols] == 2 ? 0 : 2;
      }
    }
    MousePosition(nMouseX, nMouseY);
  }

  void Logic() {

    if (GameState != GameStateRunning)
      return;

    nFlags = 0;
    int nCheck = nBombs;
    for (int x = 0; x < nCols; x++) {
      for (int y = 0; y < nRows; y++) {
        if (cPlayer[x + y * nCols] == 2) {
          if (bField[x + y * nCols])
            --nCheck;
          ++nFlags;
        }
        if (cPlayer[x + y * nCols] == 1 && nField[x + y * nCols] == 0) {
          if (bField[x + y * nCols]) {
            GameState = GameStateOver;
            break;
          }
          if (y > 0) {
            if (x > 0)
              cPlayer[(x - 1) + (y - 1) * nCols] = 1; // top-left
            cPlayer[x + (y - 1) * nCols] = 1;         // top
            if (x < nCols - 1)
              cPlayer[(x + 1) + (y - 1) * nCols] = 1; // top-right
          }
          if (x < nCols - 1) {
            cPlayer[(x + 1) + y * nCols] = 1; // right
            if (y < nRows - 1)
              cPlayer[(x + 1) + (y + 1) * nCols] = 1; // bottom-right
          }
          if (y < nRows - 1) {
            cPlayer[x + (y + 1) * nCols] = 1; // bottom
            if (x > 0)
              cPlayer[(x - 1) + (y + 1) * nCols] = 1; // bottom-left
          }
          if (x > 0)
            cPlayer[(x - 1) + y * nCols] = 1; // left
        }
      }
      if (GameState == GameStateOver) {
        audio.Play(nLoseID);
        break;
      }
    }

    if (nCheck == 0 && nFlags == nBombs) {
      GameState = GameStateWinner;
      if (fTimer < fBestTime) {
        fBestTime = fTimer;
        std::ofstream ofstr(std::filesystem::path(L".minesweeper"));
        if (ofstr.good()) {
          ofstr << fBestTime;
          ofstr.close();
        }
      }
      audio.Play(nWinID);
    }
  }

  void Draw() {

    DrawFilledRectangle(0, 0, ScreenWidth(), nFieldOffsetY, FG_GREY20);
    for (int x = 0; x < nCols; x++) {
      for (int y = 0; y < nRows; y++) {
        if (cPlayer[x + y * nCols] == 0)
          DrawBitmap(*Tiles, x * nCellSize, y * nCellSize + nFieldOffsetY, 0, 0,
                     nCellSize, nCellSize);
        else if (cPlayer[x + y * nCols] == 1) {
          DrawBitmap(*Tiles, x * nCellSize, y * nCellSize + nFieldOffsetY,
                     nCellSize, 0, nCellSize, nCellSize);
          if (nField[x + y * nCols] > 0)
            DrawString(x * nCellSize + 4, y * nCellSize + 4 + nFieldOffsetY,
                       std::to_string(nField[x + y * nCols]),
                       nColors[nField[x + y * nCols]]);
        }
        if (GameState > GameStateRunning && bField[x + y * nCols])
          DrawBitmap(*Tiles, x * nCellSize, y * nCellSize + nFieldOffsetY,
                     2 * nCellSize, 0, nCellSize, nCellSize);
        if (cPlayer[x + y * nCols] == 2)
          DrawBitmap(*Tiles, x * nCellSize, y * nCellSize + nFieldOffsetY,
                     3 * nCellSize, 0, nCellSize, nCellSize);
      }
    }
    std::stringstream ss;
    ss << "BOMBS: " << (nBombs - nFlags);
    DrawString(2, (nFieldOffsetY - 6) / 2, ss.str(), FG_GREY8);
    ss.str("");
    ss << "TIME: " << std::setw(3) << (int)fTimer;
    DrawString(ScreenWidth() - 74, 2, ss.str(), FG_GREY8);
    ss.str("");
    ss << "BEST: " << std::setw(3) << (int)fBestTime;
    DrawString(ScreenWidth() - 74, 14, ss.str(), FG_GREY12);

    if (GameState == GameStateOver)
      DrawString((ScreenWidth() - 72) / 2, (nFieldOffsetY - 8) / 2, "GAME OVER",
                 FG_RED);
    if (GameState == GameStateWinner)
      DrawString((ScreenWidth() - 48) / 2, (nFieldOffsetY - 8) / 2, "WINNER",
                 FG_RED);
    DrawString(nMouseX - 4, nMouseY - 4, "+", FG_BLACK);
  }

  void Reset() {

    GameState = GameStateRunning;

    fTimer = 0.0f;

    std::memset(bField, 0, nRows * nCols * sizeof(bool));
    std::memset(nField, 0, nRows * nCols * sizeof(int));
    std::memset(cPlayer, 0, nRows * nCols * sizeof(char));

    for (int n = 0; n < nCols * nRows / 10; n++) {
      unsigned int i = better_rand() % (nCols * nRows);
      while (bField[i])
        i = better_rand() % (nCols * nRows);
      bField[i] = true;
    }

    nBombs = std::accumulate(bField, bField + nRows * nCols, 0);

    for (int x = 0; x < nCols; x++) {
      for (int y = 0; y < nRows; y++) {
        if (bField[x + y * nCols])
          continue;
        if (y > 0) {
          if (x > 0 && bField[(x - 1) + (y - 1) * nCols])
            ++nField[x + y * nCols]; // top-left
          if (bField[x + (y - 1) * nCols])
            ++nField[x + y * nCols]; // top
          if (x < nCols - 1 && bField[(x + 1) + (y - 1) * nCols])
            ++nField[x + y * nCols]; // top-right
        }
        if (x < nCols - 1) {
          if (bField[(x + 1) + y * nCols])
            ++nField[x + y * nCols]; // right
          if (y < nRows - 1 && bField[(x + 1) + (y + 1) * nCols])
            ++nField[x + y * nCols]; // bottom-right
        }
        if (y < nRows - 1) {
          if (bField[x + (y + 1) * nCols])
            ++nField[x + y * nCols]; // bottom
          if (x > 0 && bField[(x - 1) + (y + 1) * nCols])
            ++nField[x + y * nCols]; // bottom-left
        }
        if (x > 0 && bField[(x - 1) + y * nCols])
          ++nField[x + y * nCols]; // left
      }
    }
  }

  bool bFinished = false;

  cb::SampledAudio audio;

  int nCellSize = 16;

  int nRows = 0;

  int nCols = 0;

  int nFieldOffsetY = 24;

  int nBombs = 0;

  int nFlags = 0;

  enum GameStates { GameStateRunning, GameStateOver, GameStateWinner };

  int nTickID{};

  int nLoseID{};

  int nWinID{};

  GameStates GameState = GameStateRunning;

  bool *bField = nullptr;

  int *nField = nullptr;

  char *cPlayer = nullptr;

  int nMouseX = 0;

  int nMouseY = 0;

  float fTimer = 0.0f;

  float fBestTime = 999.0f;

  static constexpr short nColors[8] = {0,       FG_BLUE,   FG_GREEN, FG_RED,
                                       FG_NAVY, FG_MAROON, FG_BROWN, FG_YELLOW};

  Bitmap *Tiles = nullptr;

  std::minstd_rand better_rand;
};

#endif // CBGLGFX_MINESWEEPER_H
