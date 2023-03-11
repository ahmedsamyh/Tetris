#pragma once
#include <MoGE/MoGE.hpp>

namespace momo {

#define LAYOUTS_CAP 256
#define UNFOCUS_OPACITY 25

struct UI {
  struct Layout {
    enum class Kind { Horz, Vert };
    Kind kind;
    Vec2 pos;
    Vec2 size;
    Vec2 padding;
    Layout();

    Vec2 availablePos() const;
    void pushWidget(Vec2 size);
  };

  size_t active_id;
  size_t id_count;
  Layout layouts[LAYOUTS_CAP];
  size_t layouts_count;
  static Vec2 btnPadding;
  bool hasFocus;
  int hoverTime;
  int hoverTimeMax;

  UI();

  void pushLayout(Layout layout);
  Layout popLayout();
  Layout *topLayout();

  void begin(Vec2 pos, Layout::Kind kind = Layout::Kind::Vert);
  bool button(std::string text, Vec2 size, Color col = Color(200, 200, 200),
              size_t id = 0);
  float slider(float val, float min, float max, float size,
               Color col = Color(200, 200, 200), size_t id = 0,
               std::string text = "");
  void text(std::string _text, size_t charSize, Color col = WHITE);
  void end();
  void input();
};

}; // namespace momo
