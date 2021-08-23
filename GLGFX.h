/**
 *  @file   GLGFX.h
 *  @brief  OpenGL Pixel Graphics
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGAMEENGINE_CBGLGFX_H
#define CBGLGAMEENGINE_CBGLGFX_H

#include "Sprite.h"

#include <string>
#include <vector>

extern "C" {
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
}

extern "C" size_t nesfont8x8_s;
extern "C" size_t nesfont8x8_sz;
extern "C" const char nesfont8x8_z[];

namespace cb {
class GLGFX;
}

typedef struct {
  float r;
  float g;
  float b;
} RGB;

typedef struct {
  uint16_t width;
  uint16_t height;
  RGB *rgb;
} Bitmap;

class cb::GLGFX {

public:
  enum [[maybe_unused]] colors{
      FG_BLACK = 0, FG_RED,     FG_GREEN,  FG_YELLOW, FG_BLUE,   FG_MAGENTA,
      FG_GREY,      FG_WHITE,   FG_CYAN,   FG_MAROON, FG_LIME,   FG_BROWN,
      FG_NAVY,      FG_FUCHSIA, FG_TEAL,   FG_GREY1,  FG_GREY2,  FG_GREY3,
      FG_GREY4,     FG_GREY5,   FG_GREY6,  FG_GREY7,  FG_GREY8,  FG_GREY9,
      FG_GREY10,    FG_GREY11,  FG_GREY12, FG_GREY13, FG_GREY14, FG_GREY15,
      FG_GREY16,    FG_GREY17,  FG_GREY18, FG_GREY20, FG_GREY21, FG_GREY22,
      FG_GREY23,    FG_GREY24,  FG_GREY25, FG_COLORS};

  GLGFX() {

    me = this;

    RGBScreenBuffer.rgb = nullptr;

    bShowFPS = true;

    bVSync = true;
  }

  void ConstructWindow(int width, int height, int pointsize, int *argc,
                       char *argv[]) {

    for (auto &c : rgb) {

      c.r /= 255.0f;
      c.g /= 255.0f;
      c.b /= 255.0f;
    }

    RGBScreenBuffer.width = width;

    RGBScreenBuffer.height = height;

    RGBScreenBuffer.rgb =
        new RGB[RGBScreenBuffer.width * RGBScreenBuffer.height];

    sFont.z_Load(nesfont8x8_z, nesfont8x8_sz, nesfont8x8_s);

    std::fill_n(RGBScreenBuffer.rgb,
                RGBScreenBuffer.width * RGBScreenBuffer.height, rgb[FG_RED]);

    nPointSize = static_cast<float>(pointsize);

    glutInit(argc, argv);

    glutInitDisplayString("rgb double samples=8 hidpi");

    glutInitWindowSize(RGBScreenBuffer.width * static_cast<int>(nPointSize),
                       RGBScreenBuffer.height * static_cast<int>(nPointSize));

    glutInitWindowPosition(
        (glutGet(GLUT_SCREEN_WIDTH) -
         RGBScreenBuffer.width * static_cast<int>(nPointSize)) /
            2,
        (glutGet(GLUT_SCREEN_HEIGHT) -
         RGBScreenBuffer.width * static_cast<int>(nPointSize)) /
            2);

    glutCreateWindow(sTitle.c_str());

    glutWMCloseFunc(WMExit);

    // glutCloseFunc( WMExit );
  }

  void Start() {

    glutDisplayFunc(Display);

    glutIdleFunc(Loop);

    glutKeyboardFunc(KeyboardDown);

    glutKeyboardUpFunc(KeyboardUp);

    glutSpecialFunc(KeyboardSpecialDown);

    glutSpecialUpFunc(KeyboardSpecialUp);

    glutSetCursor(GLUT_CURSOR_NONE);

    glutMouseFunc(Mouse);

    glutMotionFunc(MouseTrack);

    glutPassiveMotionFunc(MouseTrack);

    glutReshapeFunc(Resize);

    if (!OnUserCreate())
      return;

    clock_gettime(CLOCK_MONOTONIC_RAW, &sStartTimespec);

    std::atexit(Exit);

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    float fHalf = ((float)me->nPointSize) / 2.0f;

    gluOrtho2D(
        -fHalf,
        ((static_cast<float>(me->RGBScreenBuffer.width) * me->nPointSize)) -
            fHalf,
        (static_cast<float>(me->RGBScreenBuffer.height) * me->nPointSize) -
            fHalf,
        -fHalf);

    glRasterPos2i(0, 0);

    glDisable(GL_POINT_SMOOTH);

    glPixelZoom(nPointSize, -nPointSize);

    glutMainLoop(); // never returns :-/
  }

  [[maybe_unused]] inline bool KeyPressed(unsigned char key) {

    return bKeys[key];
  }

  [[maybe_unused]] inline bool KeyDown(unsigned char key) {

    return (!bKeysPrevious[key] && bKeys[key]);
  }

  [[maybe_unused]] inline bool KeyUp(unsigned char key) {

    return (bKeysPrevious[key] && !bKeys[key]);
  }

  [[maybe_unused]] inline bool KeySpecialPressed(int key) {

    return bSpecialKeys[key];
  }

  [[maybe_unused]] inline bool KeySpecialDown(int key) {

    return (!bSpecialKeysPrevious[key] && bSpecialKeys[key]);
  }

  [[maybe_unused]] inline bool KeySpecialUp(int key) {

    return (bSpecialKeysPrevious[key] && !bSpecialKeys[key]);
  }

  [[maybe_unused]] inline bool MousePressed(int button, int &x, int &y) const {

    if (bButton[button]) {

      x = nMouseX;

      y = nMouseY;

      return true;
    }

    return false;
  }

  [[maybe_unused]] inline bool MouseDown(int button, int &x, int &y) const {

    if (!bButtonPrevious[button] && bButton[button]) {

      x = nMouseX;

      y = nMouseY;

      return true;
    }

    return false;
  }

  [[maybe_unused]] inline bool MouseUp(int button, int &x, int &y) const {

    if (bButtonPrevious[button] && !bButton[button]) {

      x = nMouseX;

      y = nMouseY;

      return true;
    }

    return false;
  }

  [[maybe_unused]] inline void MousePosition(int &x, int &y) const {

    x = nMouseX;

    y = nMouseY;
  }

  [[maybe_unused]] [[nodiscard]] inline int ScreenWidth() const {
    return RGBScreenBuffer.width;
  }

  [[maybe_unused]] [[nodiscard]] inline int ScreenHeight() const {
    return RGBScreenBuffer.height;
  }

  [[maybe_unused]] inline void Clear(int color = FG_WHITE) {

    std::fill_n(RGBScreenBuffer.rgb,
                RGBScreenBuffer.width * RGBScreenBuffer.height, rgb[color]);
  }

  [[maybe_unused]] inline void DrawPixel(int x, int y, int color = FG_WHITE) {

    if (x >= 0 && x < RGBScreenBuffer.width && y >= 0 &&
        y < RGBScreenBuffer.height)
      RGBScreenBuffer.rgb[x + y * RGBScreenBuffer.width] = rgb[color];
  }

  [[maybe_unused]] inline void DrawLine(int x1, int y1, int x2, int y2,
                                        int color = FG_WHITE) {

    int dx = std::abs(x2 - x1);
    int sx = (x1 < x2) ? 1 : -1;
    int dy = -std::abs(y2 - y1);
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx + dy;

    while (true) {
      DrawPixel(x1, y1, color);
      if ((x1 == x2) && (y1 == y2))
        break;
      int e2 = 2 * err;
      if (e2 >= dy) {
        err += dy;
        x1 += sx;
      }
      if (e2 <= dx) {
        err += dx;
        y1 += sy;
      }
    }
  }

  [[maybe_unused]] inline void DrawTriangle(int x1, int y1, int x2, int y2,
                                            int x3, int y3,
                                            int color = FG_WHITE) {

    DrawLine(x1, y1, x2, y2, color);
    DrawLine(x2, y2, x3, y3, color);
    DrawLine(x3, y3, x1, y1, color);
  }

  [[maybe_unused]] inline void DrawFilledTriangle(int x1, int y1, int x2,
                                                  int y2, int x3, int y3,
                                                  int color = FG_WHITE) {

    if (y1 > y2) {

      std::swap(y1, y2);
      std::swap(x1, x2);
    }

    if (y2 > y3) {

      std::swap(y2, y3);
      std::swap(x2, x3);
    }

    if (y1 > y2) {

      std::swap(y1, y2);
      std::swap(x1, x2);
    }

    int a, b, y, last;

    if (y1 == y3) {

      a = b = x1;

      if (x2 < a)
        a = x2;
      else if (x2 > b)
        b = x2;

      if (x3 < a)
        a = x3;
      else if (x3 > b)
        b = x3;

      DrawLine(a, y1, b, y1, color);

      return;
    }

    int dx12 = x2 - x1, dy12 = y2 - y1, dx13 = x3 - x1, dy13 = y3 - y1,
        dx23 = x3 - x2, dy23 = y3 - y2;

    int sa = 0, sb = 0;

    if (y2 == y3)
      last = y2;
    else
      last = y2 - 1;

    for (y = y1; y <= last; y++) {

      a = x1 + sa / dy12;
      b = x1 + sb / dy13;
      sa += dx12;
      sb += dx13;
      DrawLine(a, y, b, y, color);
    }

    sa = dx23 * (y - y2);
    sb = dx13 * (y - y1);
    for (; y <= y3; y++) {
      a = x2 + sa / dy23;
      b = x1 + sb / dy13;
      sa += dx23;
      sb += dx13;
      DrawLine(a, y, b, y, color);
    }
  }

  [[maybe_unused]] inline void DrawCircle(int xc, int yc, int r,
                                          int color = FG_WHITE) {

    int x = 0;
    int y = r;
    int d = 3 - (2 * r);

    auto Bresenham = [this](int xc, int yc, int x, int y, int color) {
      DrawPixel(x + xc, y + yc, color);
      DrawPixel(x + xc, -y + yc, color);
      DrawPixel(-x + xc, -y + yc, color);
      DrawPixel(-x + xc, y + yc, color);
      DrawPixel(y + xc, x + yc, color);
      DrawPixel(y + xc, -x + yc, color);
      DrawPixel(-y + xc, -x + yc, color);
      DrawPixel(-y + xc, x + yc, color);
    };

    Bresenham(xc, yc, x, y, color);
    while (x <= y) {
      if (d <= 0)
        d = d + (4 * x++) + 6;
      else
        d = d + (4 * x++) - (4 * y--) + 10;
      Bresenham(xc, yc, x, y, color);
    }
  }

  [[maybe_unused]] inline void DrawFilledCircle(int xc, int yc, int r,
                                                int color = FG_WHITE) {

    int x = 0;
    int y = r;
    int d = 3 - (2 * r);

    auto Bresenham = [this](int xc, int yc, int x, int y, int color) {
      auto ScanLine = [this](int x0, int x1, int y, int color) {
        for (int x = x0; x <= x1; x++)
          DrawPixel(x, y, color);
      };

      ScanLine(xc - x, xc + x, yc - y, color);
      ScanLine(xc - y, xc + y, yc - x, color);
      ScanLine(xc - x, xc + x, yc + y, color);
      ScanLine(xc - y, xc + y, yc + x, color);
    };

    Bresenham(xc, yc, x, y, color);
    while (x <= y) {
      if (d <= 0)
        d = d + (4 * x++) + 6;
      else
        d = d + (4 * x++) - (4 * y--) + 10;
      Bresenham(xc, yc, x, y, color);
    }
  }

  [[maybe_unused]] inline void DrawRectangle(int x1, int y1, int x2, int y2,
                                             int color = FG_WHITE) {

    if (x1 > x2)
      std::swap(x1, x2);

    if (y1 > y2)
      std::swap(y1, y2);

    DrawLine(x1, y1, x2, y1, color);
    DrawLine(x2, y1, x2, y2, color);
    DrawLine(x2, y2, x1, y2, color);
    DrawLine(x1, y2, x1, y1, color);
  }

  [[maybe_unused]] inline void
  DrawFilledRectangle(int x1, int y1, int x2, int y2, int color = FG_WHITE) {

    if (x1 > x2)
      std::swap(x1, x2);

    if (y1 > y2)
      std::swap(y1, y2);

    for (int x = x1; x <= x2; x++) {

      if (x < 0 || x > RGBScreenBuffer.width)
        continue;

      for (int y = y1; y <= y2; y++) {

        if (y < 0 || y > RGBScreenBuffer.height)
          continue;

        RGBScreenBuffer.rgb[x + y * RGBScreenBuffer.width] = rgb[color];
      }
    }
  }

  [[maybe_unused]] inline void DrawSprite(cb::Sprite &s, int x0, int y0) {

    for (int x = 0; x < s.SpriteWidth(); x++) {
      for (int y = 0; y < s.SpriteHeight(); y++) {
        cb::Pixel pixel = s[x + y * s.SpriteWidth()];
        if (pixel.character == L' ')
          continue;
        DrawPixel(x0 + x, y0 + y, pixel.color);
      }
    }
  }

  [[maybe_unused]] inline void DrawSprite(cb::Sprite &s, int x0, int y0, int sx,
                                          int sy, int width, int height) {

    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        cb::Pixel pixel = s[(sx + x) + (y + sy) * s.SpriteWidth()];
        if (pixel.character == L' ')
          continue;
        DrawPixel(x0 + x, y0 + y, pixel.color);
      }
    }
  }

  [[maybe_unused]] void DrawString(int x0, int y0, const std::string &text,
                                   int color = FG_WHITE) {

    for (auto c : text) {
      int sx = ((c - 32) % 16) * 8;
      int sy = ((c - 32) / 16) * 8;
      for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
          cb::Pixel pixel = sFont[(sx + x) + (y + sy) * sFont.SpriteWidth()];
          if (pixel.character == L' ')
            continue;
          DrawPixel(x0 + x, y0 + y, color);
        }
      }
      x0 += 8;
    }
  }

  [[maybe_unused]] inline void DrawPixel(int x, int y, RGB color) const {

    if (x >= 0 && x < RGBScreenBuffer.width && y >= 0 &&
        y < RGBScreenBuffer.height)
      RGBScreenBuffer.rgb[x + y * RGBScreenBuffer.width] = color;
  }

  [[maybe_unused]] void DrawBitmap(Bitmap bitmap, int x0, int y0, int width,
                                   int height) const {

    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        if ((x + x0) >= 0 && (x + x0) < RGBScreenBuffer.width &&
            (y + y0) >= 0 && (y + y0) < RGBScreenBuffer.height)
          RGBScreenBuffer.rgb[(x0 + x) + (y0 + y) * RGBScreenBuffer.width] =
              bitmap.rgb[x + y * bitmap.width];
      }
    }
  }

  [[maybe_unused]] inline void DrawBitmap(Bitmap bitmap, int x0, int y0, int sx,
                                          int sy, int width, int height) const {

    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        if ((x + x0) >= 0 && (x + x0) < RGBScreenBuffer.width &&
            (y + y0) >= 0 && (y + y0) < RGBScreenBuffer.height)
          RGBScreenBuffer.rgb[(x0 + x) + (y0 + y) * RGBScreenBuffer.width] =
              bitmap.rgb[(sx + x) + (sy + y) * bitmap.width];
      }
    }
  }

  [[maybe_unused]] static void FreeBitmap(Bitmap *bitmap) {

    if (bitmap) {

      delete bitmap->rgb;
      delete bitmap;
      bitmap = nullptr;
    }
  }

  [[maybe_unused]] static Bitmap *ReadBitmap(const std::wstring &filename) {

    std::ifstream ifstr(filename, std::ios::in | std::ios::binary);

    if (!ifstr.fail())
      return ReadBitmapFromStream(ifstr);

    return nullptr;
  }

  [[maybe_unused]] static Bitmap *LoadBitMap(const char *d, std::streamsize s) {

    std::istrstream istrstr(d, s);

    return ReadBitmapFromStream(istrstr);
  }

  [[maybe_unused]] static Bitmap *z_LoadBitmap(const char *z,
                                               std::streamsize s_z, uLongf s) {

    char *d = new char[s];

    uncompress(reinterpret_cast<Bytef *>(d), &s,
               reinterpret_cast<const Bytef *>(z), s_z);

    std::istrstream istrstr(d, s);

    Bitmap *bitmap = ReadBitmapFromStream(istrstr);

    delete[] d;

    return bitmap;
  }

protected:
  std::string sTitle;

  bool bShowFPS;

  bool bVSync;

protected:
  static cb::GLGFX *me;

private:
  static Bitmap *ReadBitmapFromStream(std::istream &in) {

    unsigned char header[54];
    in.read(reinterpret_cast<char *>(&header), sizeof(header));

    auto *bitmap = new Bitmap;

    uint16_t sig;
    std::memcpy(&sig, header, sizeof(sig));
    if (sig != 0x4d42)
      return bitmap;

    std::memcpy(&bitmap->width, header + 18, sizeof(bitmap->width));
    std::memcpy(&bitmap->height, header + 22, sizeof(bitmap->height));
    bitmap->rgb = nullptr;

    if (bitmap->width * bitmap->height <= 0)
      return bitmap;

    uint16_t bpp;
    std::memcpy(&bpp, header + 28, sizeof(bpp));

    if(bpp != 24)
      return bitmap;

    bitmap->rgb = new RGB[bitmap->width * bitmap->height];

    int nPadded = (3 * bitmap->width + 3) & (~3);

    auto *row = new unsigned char[nPadded];

    for (int y = 0; y < bitmap->height; y++) {
      in.read(reinterpret_cast<char *>(row), nPadded);
      for (int x = 0; x < bitmap->width; x++) {
        bitmap->rgb[x + (bitmap->height - 1 - y) * bitmap->width].b =
            static_cast<float>(row[3 * x + 0]) / 255.0f;
        bitmap->rgb[x + (bitmap->height - 1 - y) * bitmap->width].g =
            static_cast<float>(row[3 * x + 1]) / 255.0f;
        bitmap->rgb[x + (bitmap->height - 1 - y) * bitmap->width].r =
            static_cast<float>(row[3 * x + 2]) / 255.0f;
      }
    }

    delete[] row;

    return bitmap;
  }

  cb::Sprite sFont;

  struct timespec sStartTimespec {
  }, sStopTimespec{};

  float fElapsedTime = 0.0f;

  float nPointSize{};

  Bitmap RGBScreenBuffer{};

  bool bKeys[256]{false};

  bool bKeysPrevious[256]{false};

  bool bSpecialKeys[256]{false};

  bool bSpecialKeysPrevious[256]{false};

  int nMouseX = 0;

  int nMouseY = 0;

  bool bButton[3]{false};

  bool bButtonPrevious[3]{false};

  virtual void OnUserDestroy(){};

  virtual bool OnUserResize() { return true; }

  virtual bool OnUserCreate() = 0;

  virtual bool OnUserUpdate(float fElapsedTime) = 0;

  // https://jonasjacek.github.io/colors/
  RGB rgb[40] = {{0.0f, 0.0f, 0.0f},       // black
                 {255.0f, 0.0f, 0.0f},     // red
                 {0.0f, 255.0f, 0.0f},     // green
                 {255.0f, 255.0f, 0.0f},   // yellow
                 {0.0f, 0.0f, 255.0f},     // blue
                 {255.0f, 0.0f, 255.0f},   // magenta
                 {192.0f, 192.0f, 192.0f}, // grey
                 {255.0f, 255.0f, 255.0f}, // white
                 {255.0f, 255.0f, 0.0f},   // cyan
                 {128.0f, 0.0f, 0.0f},     // maroon
                 {192.0f, 255.0f, 0.0f},   // lime
                 {139.0f, 69.0f, 19.0f},   // brown
                 {0.0f, 0.0f, 128.0f},     // navy
                 {241.0f, 156.0f, 187.0f}, // fuchsia
                 {0.0f, 128.0f, 128.0f},   // teal
                 {255.0f, 255.0f, 255.0f}, {8.0f, 8.0f, 8.0f},
                 {18.0f, 18.0f, 18.0f},    {28.0f, 28.0f, 28.0f},
                 {38.0f, 38.0f, 38.0f},    {48.0f, 48.0f, 48.0f},
                 {58.0f, 58.0f, 58.0f},    {68.0f, 68.0f, 68.0f},
                 {78.0f, 78.0f, 78.0f},    {88.0f, 88.0f, 88.0f},
                 {98.0f, 98.0f, 98.0f},    {108.0f, 108.0f, 108.0f},
                 {118.0f, 118.0f, 118.0f}, {128.0f, 128.0f, 128.0f},
                 {138.0f, 138.0f, 138.0f}, {148.0f, 148.0f, 148.0f},
                 {158.0f, 158.0f, 158.0f}, {168.0f, 168.0f, 168.0f},
                 {178.0f, 178.0f, 178.0f}, {188.0f, 188.0f, 188.0f},
                 {198.0f, 198.0f, 198.0f}, {208.0f, 208.0f, 208.0f},
                 {218.0f, 218.0f, 218.0f}, {228.0f, 228.0f, 228.0f},
                 {238.0f, 238.0f, 238.0f}};

  static void Display() {

    glDrawPixels(me->RGBScreenBuffer.width, me->RGBScreenBuffer.height, GL_RGB,
                 GL_FLOAT, me->RGBScreenBuffer.rgb);

    if (!me->bVSync) {
      GLint sync = 0;
      CGLContextObj ctx = CGLGetCurrentContext();
      CGLSetParameter(ctx, kCGLCPSwapInterval, &sync);
    }

    glutSwapBuffers();
  }

  static void Loop() {

    clock_gettime(CLOCK_MONOTONIC_RAW, &(me->sStopTimespec));

    me->fElapsedTime =
        (float)(me->sStopTimespec.tv_sec - me->sStartTimespec.tv_sec) +
        (float)(me->sStopTimespec.tv_nsec - me->sStartTimespec.tv_nsec) /
            1000000000.0f;

    std::string title = me->sTitle;

    if (me->bShowFPS)
      title += " - FPS: " + std::to_string((int)(1.0f / me->fElapsedTime));

    glutSetWindowTitle(title.c_str());

    if (!me->OnUserUpdate(me->fElapsedTime))
      exit(0);

    glutPostRedisplay();

    std::memcpy(me->bKeysPrevious, me->bKeys, sizeof(me->bKeys));

    std::memcpy(me->bSpecialKeysPrevious, me->bSpecialKeys,
                sizeof(me->bSpecialKeys));

    std::memcpy(me->bButtonPrevious, me->bButton, sizeof(me->bButton));

    me->sStartTimespec = me->sStopTimespec;
  }

  static void KeyboardDown(unsigned char key, int x, int y) {

    me->bKeys[key] = true;
  }

  static void KeyboardUp(unsigned char key, int x, int y) {

    me->bKeys[key] = false;
  }

  static void KeyboardSpecialDown(int key, int x, int y) {

    me->bSpecialKeys[key] = true;
  }

  static void KeyboardSpecialUp(int key, int x, int y) {

    me->bSpecialKeys[key] = false;
  }

  static void Mouse(int button, int state, int x, int y) {

    switch (button) {
    case GLUT_LEFT_BUTTON:
      me->bButton[0] = state == GLUT_DOWN;
      break;
    case GLUT_MIDDLE_BUTTON:
      me->bButton[2] = state == GLUT_DOWN;
      break;
    case GLUT_RIGHT_BUTTON:
      me->bButton[1] = state == GLUT_DOWN;
    default:
      break;
    }

    me->nMouseX = x;
    me->nMouseY = y;
  }

  static void MouseTrack(int x, int y) {

    me->nMouseX = x;
    me->nMouseY = y;

    if (me->nMouseX < 0)
      me->nMouseX = 0;
    if (me->nMouseX >= me->RGBScreenBuffer.width)
      me->nMouseX = me->RGBScreenBuffer.width - 1;
    if (me->nMouseY < 0)
      me->nMouseY = 0;
    if (me->nMouseY >= me->RGBScreenBuffer.height)
      me->nMouseY = me->RGBScreenBuffer.height - 1;
  }

  static void Resize(int width, int height) {

    if (!me->OnUserResize())
      exit(0);

    // me->RGBScreenBuffer.width = 2 * width / me->nPointSize;

    // me->RGBScreenBuffer.height = 2 * height / me->nPointSize;
  }

  static void WMExit() { exit(0); }

  static void Exit() {

    me->OnUserDestroy();

    delete me->RGBScreenBuffer.rgb;
  }
};

cb::GLGFX *cb::GLGFX::me = nullptr;

#endif // CBGLGAMEENGINE_CBGLGFX_H
