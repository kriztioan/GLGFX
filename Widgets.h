/**
 *  @file   Widgets.h
 *  @brief  Widgets using CBGLGFX
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2023-06-23
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGAMEENGINE_WIDGETS_H
#define CBGLGAMEENGINE_WIDGETS_H

#include <array>
#include <memory>
#include <string>
#include <vector>

#include "GLGFX.h"

namespace cb {
class Widget;
class Widgets;
class WidgetButton;
class WidgetRadioGroup;
} // namespace cb

class cb::Widget {
public:
  virtual ~Widget(){};
  virtual Widget *clone() = 0;
  virtual void draw(GLGFX *glgfx) = 0;
  virtual bool hit(int x, int y) = 0;
};

class cb::Widgets {
public:
  void add(Widget &widget) {
    widgets.emplace_back(std::unique_ptr<Widget>(widget.clone()));
  }

  void update() {

    int x;
    int y;

    if (glgfx->MouseUp(GLUT_LEFT_BUTTON, x, y)) {
      for (auto &widget : widgets) {

        widget->hit(x, y);
      }
    }

    for (auto &widget : widgets) {
      widget->draw(glgfx);
    }

    glgfx->MousePosition(x, y);

    glgfx->DrawFilledTriangle(x, y, x + 4, y, x, y + 4, cb::GLGFX::FG_YELLOW);

    glgfx->DrawFilledTriangle(x + 1, y + 3, x + 3, y + 5, x + 3, y + 1,
                              cb::GLGFX::FG_YELLOW);

    glgfx->DrawFilledTriangle(x + 3, y + 1, x + 5, y + 3, x + 3, y + 5,
                              cb::GLGFX::FG_YELLOW);
  }

  GLGFX *glgfx;

private:
  std::vector<std::unique_ptr<Widget>> widgets;
};

class cb::WidgetButton : public cb::Widget {

public:
  WidgetButton *clone() final { return new WidgetButton(*this); }

  std::string text;
  int xpos = 0;
  int ypos = 0;
  int width = 50;
  int height = 13;
  int color = 0;
  int border = 1;

  void *userdata = nullptr;

  bool (*callback)(WidgetButton *button, void *userdata);

  bool hit(int x, int y) final {

    if (x >= xpos && y >= ypos && x <= xpos + width && y <= ypos + height) {

      return callback(this, userdata);
    }

    return false;
  }

  void draw(GLGFX *glgfx) final {

    glgfx->DrawRectangle(xpos, ypos, xpos + width - 1, ypos + height - 1,
                         border);
    glgfx->DrawFilledRectangle(xpos + 1, ypos + 1, xpos + width - 2,
                               ypos + height - 2, color);
    glgfx->DrawString(xpos + 3, ypos + 3, text, border);
  }
};

class cb::WidgetRadioGroup : public cb::Widget {
public:
  WidgetRadioGroup() = default;
  WidgetRadioGroup(WidgetRadioGroup &other) {
    for (auto &button : other.buttons) {
      WidgetButton *button_ptr = button->clone();
      buttons.emplace_back(std::unique_ptr<WidgetButton>(button_ptr));
      if (button.get() == other.sel) {
        sel = button_ptr;
      }
    }
  }
  WidgetRadioGroup *clone() final { return new WidgetRadioGroup(*this); }
  void draw(GLGFX *glgfx) {
    for (auto &button : buttons) {
      button->draw(glgfx);
      glgfx->DrawFilledCircle(
          button->xpos + button->width - 7, button->ypos + button->height / 2,
          2, button.get() == sel ? cb::GLGFX::FG_YELLOW : cb::GLGFX::FG_GREY8);
      glgfx->DrawCircle(button->xpos + button->width - 7,
                        button->ypos + button->height / 2, 3,
                        cb::GLGFX::FG_GREY10);
    }
  }
  bool hit(int x, int y) final {
    if (sel) {
      if (x >= sel->xpos && y >= sel->ypos && x <= sel->xpos + sel->width &&
          y <= sel->ypos + sel->height) {
        return false;
      }
    }

    for (auto &button : buttons) {
      if (button.get() == sel) {
        continue;
      }
      if (button->hit(x, y)) {
        sel = button.get();
      }
    }
    return true;
  }
  bool select(size_t index) {
    if (buttons.size() > 0 && index < buttons.size()) {
      sel = buttons[index].get();
      return true;
    }
    return false;
  }
  void add(WidgetButton &button) {
    buttons.emplace_back(std::unique_ptr<WidgetButton>(button.clone()));
  }

private:
  std::vector<std::unique_ptr<WidgetButton>> buttons;
  WidgetButton *sel = nullptr;
};

#endif