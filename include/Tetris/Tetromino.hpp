#pragma once
#include <MoGE/MoGE.hpp>
#include <Tetris/Block.hpp>

using namespace momo;

struct Block;

struct Tetromino {
  enum class Type { Straight, Square, T, L, Skew };
  Type type;
  std::vector<Block> blocks;
  Vec2 pos;
  bool active;

  Tetromino(Vec2 _pos = {0, 0});

  // setters
  void setType(Type t);

  // methods
  void update(float delta);
  void draw();
  bool checkDown(Tetromino &other);
};
