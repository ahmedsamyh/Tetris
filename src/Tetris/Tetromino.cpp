#include <Tetris/Tetromino.hpp>

Tetromino::Tetromino(Vec2 _pos) {
  ///
  pos = _pos;
  setType(Type::Straight);
};

// setters
void Tetromino::setType(Type t) {
  type = t;
  switch (type) {
  case Type::Straight:
    for (size_t i = 0; i < 4; ++i) {
      Block b;
      b.offset = Vec2(float(i * TILE_SIZE), 0.f);
      blocks.push_back(b);
    }
    break;
  case Type::Square:
    for (size_t i = 0; i < 2; ++i) {
      Block b;
      b.offset = Vec2(float(i * TILE_SIZE), 0.f);
      blocks.push_back(b);
    }
    for (size_t i = 0; i < 2; ++i) {
      Block b;
      b.offset = Vec2(float(i * TILE_SIZE), TILE_SIZE);
      blocks.push_back(b);
    }
    break;
  case Type::T:
    break;
  case Type::L:
    break;
  case Type::Skew:
    break;
  default:
    UNREACHABLE();
    break;
  };
}

// methods
void Tetromino::update(float delta) {
  for (auto &b : blocks) {
    b.update(delta);
    b.pos = pos + b.offset;
  }
};
void Tetromino::draw() {
  for (auto &b : blocks) {
    b.draw();
    if (active)
      drawRect(b.pos - Vec2(1, 1), Vec2(TILE_SIZE + 1, TILE_SIZE + 1), RED);
  }
};

bool Tetromino::checkDown(Tetromino &other) {
  ///
  for (auto &b : blocks) {
    for (auto &otherB : other.blocks) {
      if (b.pos.x == otherB.pos.x && b.pos.y + TILE_SIZE >= otherB.pos.y)
        return true;
    };
  };
  return false;
};
