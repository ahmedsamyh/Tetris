#include <Tetris/Block.hpp>

using namespace momo;

Block::Block() {
  offset = {0.f, 0.f};
  pos = {0.f, 0.f};
  hitbox = {TILE_SIZE, TILE_SIZE};
  spr.init("block");
  spr.setOrigin();
  // TODO: Color will be choosed from a color set later
  setColor(WHITE);
};

// setters
void Block::setColor(Color col) { spr.setColor(col); };

// methods
void Block::update(float delta) { spr.setPosition(pos); };

void Block::draw() {
  ///
  drawSprite(spr);
};
