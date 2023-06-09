#pragma once
#include <Global.hpp>

using namespace momo;

struct Block {
  Sprite spr;
  Vec2 offset;
  Vec2 pos;
  Vec2 hitbox;

  Block();

  // setters
  void setColor(Color col);

  // methods
  void update(float delta);
  void draw();
};
