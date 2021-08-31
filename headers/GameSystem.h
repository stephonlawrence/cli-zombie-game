#pragma once

#include <string>
#include "Player.h"
#include "Level.h"
#include "ErrorLog.h"
#include "Timer.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "GameState.h"

class GameSystem{
public:
  GameSystem(std::string filename);

  GameState playGame();
  void stop();
  void processInput();
  void processEnemyMove();

private:
  Level _level;
  Player _player;
  GameState _state;
  std::vector <Player> _enemies;
  Timer _etimer;
  Timer _gtimer;
};
