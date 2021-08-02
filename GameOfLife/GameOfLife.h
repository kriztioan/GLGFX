/**
 *  @file   GameOfLife.h
 *  @brief  Game of Life in CBGLGFX
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGFX_GAMEOFLIFE_H_
#define CBGLGFX_GAMEOFLIFE_H_

#include "../GLGFX.h"
#include <vector>

template <class T> class Grid {

public:
  void resize(size_t ncols, size_t nrows) {
    rows = nrows;
    cols = ncols;
    cells.resize(nrows * ncols);
  }

  T &at(int pos) {
    return cells.at((pos % cells.size() + cells.size()) % cells.size());
  }

  T &at(int col, int row) {
    return cells.at((col % cols + cols) % cols +
                    cols * ((row % rows + rows) % rows));
  }

  T &operator[](int pos) { return at(pos); }

  int nrows() { return rows; }

  int ncols() { return cols; }

private:
  std::vector<T> cells;
  int rows;
  int cols;
};

struct Cell {
  bool bAlive = false;
};

class GameOfLife : public cb::GLGFX {

  bool OnUserCreate() final {

    grid.resize(ScreenWidth(), ScreenHeight());

    tmp = grid;

    Reset();

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) final {

    if (KeyUp('q'))
      return false;

    if (KeyUp('n') && bStep)
      Evolve();

    if (KeyUp('s'))
      bStep = !bStep;

    if (KeyUp('r'))
      Reset();

    fTimer += fElapsedTime;

    if (fTimer > 0.1 && !bStep) {
      Evolve();
      fTimer = 0.0f;
    }

    Draw();

    return true;
  }

  void Draw() {
    for (size_t x = 0; x < grid.ncols(); x++)
      for (size_t y = 0; y < grid.nrows(); y++)
        DrawPixel(x, y, grid.at(x, y).bAlive ? FG_WHITE : FG_MAROON);
  }

  void Evolve() {
    for (size_t x = 0; x < grid.ncols(); x++) {
      for (size_t y = 0; y < grid.nrows(); y++) {
        int nAliveNeighbors = 0;
        for (int dx = -1; dx < 2; dx++) {
          for (int dy = -1; dy < 2; dy++) {
            if (dx == 0 && dy == 0)
              continue;
            if (grid.at(x + dx, y + dy).bAlive)
              ++nAliveNeighbors;
          }
        }

        if (grid.at(x, y).bAlive)
          tmp.at(x, y).bAlive = !(nAliveNeighbors < 2 || nAliveNeighbors > 3);
        else if (nAliveNeighbors == 3)
          tmp.at(x, y).bAlive = true;
      }
    }
    grid = tmp;
  }

  void Reset() {

    for (int i = 0; i < (grid.ncols() * grid.nrows()); i++)
      grid[i].bAlive = false;
    tmp = grid;

    int nAutomaton = ScreenHeight() * ScreenWidth() / 4000;

    for (int i = 0; i < nAutomaton; i++)
      AddGlider(rand() % ScreenWidth(), rand() % ScreenHeight());

    for (int i = 0; i < nAutomaton; i++)
      AddExploder(rand() % ScreenWidth(), rand() % ScreenHeight());

    for (int i = 0; i < nAutomaton; i++)
      AddSmallExploder(rand() % ScreenWidth(), rand() % ScreenHeight());

    for (int i = 0; i < nAutomaton; i++)
      AddTenRow(rand() % ScreenWidth(), rand() % ScreenHeight());

    for (int i = 0; i < nAutomaton; i++)
      AddSpaceship(rand() % ScreenWidth(), rand() % ScreenHeight());
  }

  void AddGlider(int x0, int y0) {
    static constexpr int Glider[][3] = {{0, 0, 1}, {1, 0, 1}, {0, 1, 1}};
    for (int dx = 0; dx < 3; dx++) {
      for (int dy = 0; dy < 3; dy++) {
        grid.at(x0 + dx, y0 + dy).bAlive = Glider[dx][dy];
      }
    }
  }

  void AddExploder(int x0, int y0) {
    static constexpr int Exploder[][5] = {{1, 1, 1, 1, 1},
                                          {0, 0, 0, 0, 0},
                                          {1, 0, 0, 0, 1},
                                          {0, 0, 0, 0, 0},
                                          {1, 1, 1, 1, 1}};
    for (int dx = 0; dx < 5; dx++) {
      for (int dy = 0; dy < 5; dy++) {
        grid.at(x0 + dx, y0 + dy).bAlive = Exploder[dx][dy];
      }
    }
  }

  void AddSmallExploder(int x0, int y0) {
    static constexpr int SmallExploder[3][4] = {
        {0, 1, 1, 0}, {1, 1, 0, 1}, {0, 1, 1, 0}};
    for (int dx = 0; dx < 3; dx++) {
      for (int dy = 0; dy < 4; dy++) {
        grid.at(x0 + dx, y0 + dy).bAlive = SmallExploder[dx][dy];
      }
    }
  }

  void AddTenRow(int x0, int y0) {
    for (int dx = 0; dx < 10; dx++)
      grid.at(x0 + dx, y0).bAlive = true;
  }

  void AddSpaceship(int x0, int y0) {
    static constexpr int Spaceship[5][4] = {
        {0, 1, 0, 1}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 1}, {1, 1, 1, 0}};
    for (int dx = 0; dx < 5; dx++) {
      for (int dy = 0; dy < 4; dy++) {
        grid.at(x0 + dx, y0 + dy).bAlive = Spaceship[dx][dy];
      }
    }
  }

  float fTimer = 0.0f;

  bool bStep = false;

  Grid<Cell> grid;
  Grid<Cell> tmp;

public:
  GameOfLife() { sTitle = "Game of Life"; }
};

#endif // CBGLGFX_GAMEOFLIFE_H_
