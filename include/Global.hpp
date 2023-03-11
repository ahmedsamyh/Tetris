#pragma once
#include <MoGE/MoGE.hpp>
#include <Tetris/Block.hpp>
#include <Tetris/Tetromino.hpp>

using namespace momo;

#define TILE_SIZE 32
#define SCREEN_SIZE Vec2(TILE_SIZE * 20, TILE_SIZE * 20)
#define PLAY_OFF Vec2(TILE_SIZE * 2, TILE_SIZE * 2)
#define PLAY_AREA Vec2(TILE_SIZE * 12, TILE_SIZE * 16)

struct Tetromino;
struct Block;

struct G {
  static std::vector<Tetromino> tetrominos;
};
