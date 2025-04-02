/**
 *  @file   Snake.h
 *  @brief  Snake in CBGLGFX
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-09-21
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGFX_SNAKE_H_
#define CBGLGFX_SNAKE_H_

#include "../GLGFX.h"

#include <algorithm>
#include <array>
#include <sstream>

class Snake : public cb::GLGFX {

public:
  Snake() {
    sTitle = "Snake";
    bShowFPS = false;
  }

private:
  bool OnUserCreate() final {

    Reset();

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) final {

    Input();

    fCharmLifeSpan -= fElapsedTime;

    fAccumulator += fElapsedTime;
    if (fAccumulator < fSpeed) {
      return !bFinished;
    }

    fAccumulator -= fSpeed;

    if (bGameOver || bPaused) {
      return !bFinished;
    }

    if (fCharmLifeSpan < 0.0f) {
      PlaceCharm();
    }

    int16_t cCol, cRow;

    if (aField[head + dir] < hit) {

      head += dir;
      cCol = head % cCols;
      cRow = head / cCols;
      DrawFilledRectangle(cCol * nCellSize, cRow * nCellSize,
                          (cCol + 1) * nCellSize - 1,
                          (cRow + 1) * nCellSize - 1, FG_RED);

      DrawString((ScreenWidth() - 80) / 2, (ScreenHeight() - 16) / 2,
                 "GAME OVER!", FG_RED);

      bGameOver = true;

      if (bGameOver && score > highscore) {
        highscore = score;
        std::ofstream ofstr(std::filesystem::path(L".snake"));
        if (ofstr.good()) {
          ofstr << highscore;
          ofstr.close();
        }
      }

      return !bFinished;
    }

    aField[head] = dir;
    head += dir;

    if (aField[head] == 127) {

      cCol = tail % cCols;
      cRow = tail / cCols;
      DrawFilledRectangle(cCol * nCellSize, cRow * nCellSize,
                          (cCol + 1) * nCellSize - 1,
                          (cRow + 1) * nCellSize - 1, FG_BLACK);

      uint16_t tmp = tail + aField[tail];
      aField[tail] = 127;
      if (head == tail) {
        tail += dir;
      } else {
        tail = tmp;
      }
    } else {
      ++score;
      DrawScore();
      PlaceCharm();
    }

    aField[head] = dir;

    cCol = head % cCols;
    cRow = head / cCols;
    DrawFilledRectangle(cCol * nCellSize, cRow * nCellSize,
                        (cCol + 1) * nCellSize - 1, (cRow + 1) * nCellSize - 1,
                        FG_MAROON);

    return !bFinished;
  }

  void DrawScore() {
    std::stringstream ss;
    ss << score << '/' << highscore;
    std::string score_str(ss.str());
    DrawFilledRectangle(ScreenWidth() / 2 - 4 * 8, 0,
                        ScreenWidth() / 2 + 4 * 8 - 1, 8 - 1, FG_NAVY);
    DrawString((ScreenWidth() - 8 * score_str.length()) / 2, 1, score_str,
               FG_YELLOW);
  }

  void PlaceCharm() {
    fCharmLifeSpan = 3.5f;
    aField[charm] = 127;
    uint16_t cCol = charm % cCols, cRow = charm / cCols;
    DrawFilledRectangle(cCol * nCellSize, cRow * nCellSize,
                        (cCol + 1) * nCellSize - 1, (cRow + 1) * nCellSize - 1,
                        FG_BLACK);
    do {
      charm = (uint16_t)rand() % (cRows * cCols);
    } while (aField[charm] != 127);
    aField[charm] = 64;
    cCol = charm % cCols;
    cRow = charm / cCols;
    DrawFilledCircle(cCol * nCellSize + nCellSize / 2,
                     cRow * nCellSize + nCellSize / 2, nCellSize / 2 - 1,
                     FG_CYAN);
  }

  void Input() {

    if (KeyUp('q')) {
      bFinished = true;
    }
    if (KeyUp('p')) {
      bPaused = !bPaused;
    }
    if (KeyUp(' ') && bGameOver) {
      Reset();
    }
    if (KeySpecialDown(GLUT_KEY_UP)) {
      dir = -cCols;
    }
    if (KeySpecialDown(GLUT_KEY_DOWN)) {
      dir = cCols;
    }
    if (KeySpecialDown(GLUT_KEY_LEFT)) {
      dir = -1;
    }
    if (KeySpecialDown(GLUT_KEY_RIGHT)) {
      dir = 1;
    }
  }

  void Reset() {

    bGameOver = false;

    dir = -1;

    std::fill(aField.begin(), aField.end(), 127);

    Clear(FG_BLACK);

    for (uint16_t cCol = 0; cCol < cCols; cCol++) {
      aField[cCol] = aField[cCol + (cRows - 1) * cCols] = -128;

      DrawFilledRectangle(cCol * nCellSize, 0, (cCol + 1) * nCellSize - 1,
                          nCellSize - 1, FG_NAVY);
      DrawFilledRectangle(cCol * nCellSize, (cRows - 1) * nCellSize,
                          (cCol + 1) * nCellSize - 1, cRows * nCellSize - 1,
                          FG_NAVY);
    }

    for (uint16_t cRow = 1; cRow < (cRows - 1); cRow++) {
      aField[cRow * cCols] = aField[cRow * cCols + cCols - 1] = -128;
      DrawFilledRectangle(0, cRow * nCellSize, nCellSize - 1,
                          (cRow + 1) * nCellSize - 1, FG_NAVY);
      DrawFilledRectangle((cCols - 1) * nCellSize, cRow * nCellSize,
                          cCols * nCellSize - 1, (cRow + 1) * nCellSize - 1,
                          FG_NAVY);
    }

    score = 0;
    std::ifstream ifstr(std::filesystem::path(L".snake"));
    if (ifstr.good()) {
      ifstr >> highscore;
      ifstr.close();
    }
    DrawScore();

    tail = head = cRows * cCols / 2 + cCols / 2;
    aField[tail] = dir;

    uint16_t cCol = tail % cCols, cRow = tail / cCols;
    DrawFilledRectangle(cCol * nCellSize, cRow * nCellSize,
                        (cCol + 1) * nCellSize - 1, (cRow + 1) * nCellSize - 1,
                        FG_RED);

    PlaceCharm();
  }

  static constexpr int8_t cRows = 30;

  static constexpr int8_t cCols = 20;

  static constexpr uint16_t nCellSize = 8;

  static constexpr float fSpeed = 0.1f;

  static constexpr int8_t hit = cCols + 1;

  std::array<int8_t, cRows * cCols> aField;

  int8_t dir;

  bool bFinished = false;

  bool bPaused = false;

  bool bGameOver;

  uint16_t head, tail, charm = cCols + 2, score, highscore = 0;

  float fCharmLifeSpan;

  float fAccumulator = 0.0f;
};

#endif // CBGLGFX_SNAKE_H_
