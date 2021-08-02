/**
 *  @file   GFXEngine.h
 *  @brief  GFX Engine in CBGLGFX
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGFX_GFXENGINE_H_
#define CBGLGFX_GFXENGINE_H_

#include "../GFX3D.h"
#include "../GLGFX.h"

#include <codecvt>
#include <iostream>
#include <list>
#include <locale>

class GFXEngine : public cb::GLGFX {

public:
  GFXEngine(int argc, char *argv[]) {

    if (argc > 1) {
      std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> conv;
      model = conv.from_bytes(argv[1]);
    } else {
      std::cerr << "please provide a model\n";
      exit(1);
    }

    sTitle = "GFX Engine";

    bShowFPS = true;

    bVSync = false;
  }

  bool OnUserCreate() override {

    vCamera = {0.0f, 0.0f, 0.0f};

    fAngle = 0.0f;

    fYaw = 0.0f;

    fNear = 0.1f;

    mProj = ProjectionMatrix(fNear, 1000.0f, 90.0f,
                             (float)ScreenHeight() / (float)ScreenWidth()) *
            ScalingMatrix(-1.0f, -1.0f, 1.0f) *
            TranslationMatrix(1.0f, 1.0f, 1.0f) *
            ScalingMatrix(0.5f * (float)ScreenWidth(),
                          0.5f * (float)ScreenHeight(), 1.0f);

    mTrans = TranslationMatrix(0.0f, 0.0f, 16.0f);

    vIllumination = {0.0f, 0.0f, -1.0f};

    // vIllumination = vIllumination.normalize();

    vUp = {0.0f, 1.0f, 0.0f};

    vView = {0.0f, 0.0f, 1.0f};

    return mObj.ReadObj(model);
  }

  bool OnUserUpdate(float fElapsedTime) override {

    if (KeyUp('q'))
      return false;

    if (KeySpecialPressed(GLUT_KEY_UP))
      vCamera.y += 10.0f * fElapsedTime;

    if (KeySpecialPressed(GLUT_KEY_DOWN))
      vCamera.y -= 10.0f * fElapsedTime;

    if (KeySpecialPressed(GLUT_KEY_LEFT))
      vCamera.x += 10.0f * fElapsedTime;

    if (KeySpecialPressed(GLUT_KEY_RIGHT))
      vCamera.x -= 10.0f * fElapsedTime;

    cb::vec3d vForward = vView * 12.0f * fElapsedTime;

    if (KeyPressed('w'))
      vCamera += vForward;

    if (KeyPressed('s'))
      vCamera -= vForward;

    if (KeyPressed('d'))
      fYaw -= 1.2f * fElapsedTime;

    if (KeyPressed('a'))
      fYaw += 1.2f * fElapsedTime;

    cb::mat4x4 mWorld =
        RotationMatrixZ(fAngle) * RotationMatrixX(fAngle * 0.5f) * mTrans;

    cb::vec3d vTarget = {0.0f, 0.0f, 1.0f};

    vView = RotationMatrixY(fYaw) * vTarget;

    vTarget = vCamera + vView;

    cb::mat4x4 mView = ViewMatrix(vCamera, vTarget, vUp);

    std::vector<cb::triangle3d> vRasterize;

    for (auto t : mObj.triangles) {

      t = mWorld * t;

      cb::vec3d normal = (t.p2 - t.p1).cross(t.p3 - t.p1).normalize();

      if ((normal * (t.p1 - vCamera)) >= 0.0f)
        continue;

      t = mView * t;

      cb::triangle3d tClipped[2];

      t.color = FG_GREY2 + (int)(24.0f * std::fabs(normal * vIllumination));

      int nClipped = Clip({0.0f, 0.0f, fNear}, {0.0f, 0.0f, 1.0f}, t,
                          tClipped[0], tClipped[1]);

      for (int n = 0; n < nClipped; n++) {

        t = mProj * tClipped[n];

        vRasterize.emplace_back(t);
      }
    }

    std::sort(vRasterize.begin(), vRasterize.end(),
              [](const cb::triangle3d &a, const cb::triangle3d &b) {
                return ((a.p1.z + a.p2.z + a.p3.z)) <
                       ((b.p1.z + b.p2.z + b.p3.z));
              });

    Clear(FG_NAVY);

    for (auto triangle : vRasterize) {

      cb::triangle3d tClipped[2];

      std::list<cb::triangle3d> lTriangles;

      int nTriangles = 1;

      lTriangles.push_back(triangle);

      for (int p = 0; p < 4; p++) {

        int nTrianglesToAdd = 0;

        while (nTriangles > 0) {

          cb::triangle3d t = lTriangles.front();

          lTriangles.pop_front();

          --nTriangles;

          switch (p) {

          case 0:
            nTrianglesToAdd = Clip({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, t,
                                   tClipped[0], tClipped[1]);
            break;
          case 1:
            nTrianglesToAdd =
                Clip({0.0f, (float)ScreenHeight() - 1.0f, 0.0f},
                     {0.0f, -1.0f, 0.0f}, t, tClipped[0], tClipped[1]);
            break;
          case 2:
            nTrianglesToAdd = Clip({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, t,
                                   tClipped[0], tClipped[1]);
            break;
          case 3:
            nTrianglesToAdd =
                Clip({(float)ScreenWidth() - 1.0f, 0.0f, 0.0f},
                     {-1.0f, 0.0f, 0.0f}, t, tClipped[0], tClipped[1]);
          default:
            break;
          }

          for (int q = 0; q < nTrianglesToAdd; q++)
            lTriangles.push_back(tClipped[q]);
        }

        nTriangles = lTriangles.size();
      }

      for (auto t : lTriangles) {

        DrawFilledTriangle((int)t.p1.x, (int)t.p1.y, (int)t.p2.x, (int)t.p2.y,
                           (int)t.p3.x, (int)t.p3.y, t.color);

        /*DrawTriangle(t.p1.x, t.p1.y,
                     t.p2.x, t.p2.y,
                     t.p3.x, t.p3.y, FG_YELLOW);*/
      }
    }

    int nMouseX;

    int nMouseY;

    MousePosition(nMouseX, nMouseY);

    DrawString(10, 10,
               "(" + std::to_string(nMouseX) + "," + std::to_string(nMouseY) +
                   ")",
               FG_YELLOW);

    DrawLine(nMouseX - 4, nMouseY, nMouseX + 4, nMouseY, FG_YELLOW);

    DrawLine(nMouseX, nMouseY - 4, nMouseX, nMouseY + 4, FG_YELLOW);

    return true;
  }

  std::wstring model;

  cb::mesh mObj;

  float fAngle = 0.0f;

  float fYaw = 0.0f;

  float fNear = 0.0f;

  cb::mat4x4 mProj;

  cb::mat4x4 mTrans;

  cb::vec3d vCamera;

  cb::vec3d vView;

  cb::vec3d vUp;

  cb::vec3d vIllumination;
};

#endif // CBGLGFX_GFXENGINE_H_
