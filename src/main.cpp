#include <Global.hpp>
#include <MoGE/MoGE.hpp>
#include <MoUI/MoUI.hpp>
#include <format>
#include <iostream>

using namespace momo;

#define W 800.f
#define H 800.f

struct MainScene : public Scene {
  Sprite bgSpr;
  bool canSpawn = true;
  Alarm moveAlarm = true;
  int activeTetr = -1;
  UI ui;
  bool DEBUG_DRAW = false;
  MainScene() {
    ///
    id = 0;
    setBlendMode(sf::BlendAlpha);
    bgSpr.init("block");
    bgSpr.spr.setTextureRect(sf::IntRect(0, 0, (int)SW, (int)SH));
    bgSpr.setOrigin();

    moveAlarm.init(0.5f);
  };

  void init() override{
      ///
  };

  void input() override {
    if (keyPressed(Tilde))
      DEBUG_DRAW = !DEBUG_DRAW;
    // if (mousePressed(BTN_LEFT)) {
    // Vec2 pos;
    // pos.x = float(int(M2.x / TILE_SIZE) * TILE_SIZE);
    // pos.y = float(int(M2.y / TILE_SIZE) * TILE_SIZE);
    // Tetromino t(pos);
    // G::tetrominos.push_back(t);
    // }
  };

  void update(float dt) override {
    ///
    if (canSpawn) {
      canSpawn = false;
      Vec2 actualPos = {PLAY_OFF.x + random(PLAY_AREA.x - (TILE_SIZE * 4)),
                        PLAY_OFF.y};
      Vec2 pos;
      pos.x = float(int(actualPos.x / TILE_SIZE) * TILE_SIZE);
      pos.y = float(int(actualPos.y / TILE_SIZE) * TILE_SIZE);
      Tetromino t(pos);
      G::tetrominos.push_back(t);
      activeTetr++;
    };
    auto &a = G::tetrominos[activeTetr];

    for (size_t i = 0; i < G::tetrominos.size(); ++i) {
      auto &t = G::tetrominos[i];
      t.update(dt);
      t.active = activeTetr == i;
    };

    // MOVEMENT AND COLLISION
    if (moveAlarm.onAlarm(dt)) {
      bool canMove = true;
      auto &a = G::tetrominos[activeTetr];
      // collision with other tetrominos
      for (size_t i = 0; i < G::tetrominos.size(); ++i) {
        if (activeTetr != i && a.checkDown(G::tetrominos[i])) {
          canMove = false;
        };
      };

      // collision with floor
      if (a.pos.y + TILE_SIZE >= (PLAY_OFF.y + PLAY_AREA.y))
        canMove = false;

      if (canMove)
        a.pos.y += TILE_SIZE;
      else
        canSpawn = true;
    }

    /// HORIZONTAL MOVEMENT
    // assumes the first block is the leftmost and the last block is the
    // rightmost
    if (keyPressed(Left)) {
      // TODO: doesn't check with other tetrominos yet
      if (a.blocks[0].pos.x - TILE_SIZE >= PLAY_OFF.x)
        a.pos.x -= TILE_SIZE;
    };
    if (keyPressed(Right)) {
      // TODO: doesn't check with other tetrominos yet
      if (a.blocks.back().pos.x + TILE_SIZE * 2 <= PLAY_OFF.x + PLAY_AREA.x)
        a.pos.x += TILE_SIZE;
    };
  };

  void draw() override {
    ///
    drawSprite(bgSpr);
    fillRect(PLAY_OFF, PLAY_AREA, BLACK, RED);

    for (auto &t : G::tetrominos) {
      t.draw();
    };

    setCharSize(TILE_SIZE / 2);
    drawText(PLAY_OFF + Vec2(PLAY_AREA.x, 0.f), "Score: ");
    if (DEBUG_DRAW) {
      ui.begin(Vec2(2, 2));
      ui.text(std::format("Tetrominos Size: {}", G::tetrominos.size()),
              TILE_SIZE / 2);

      ui.end();
    }
  };
};

int main(int argc, const char **argv) {
  MAIN(MainScene);
  create("Tetris", SCREEN_SIZE.x, SCREEN_SIZE.y);
  run();
  return 0;
}
