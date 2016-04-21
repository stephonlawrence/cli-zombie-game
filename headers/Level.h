#pragma once

#include "ErrorLog.h"
#include "Player.h"

#include <fstream>
#include <string>
#include <vector>
#include <curses.h>
#include <iostream>
#include <cmath>

#include <vector>

class Level{
public:
  void load(std::string, Player &player, std::vector<Player> &enemies);
  void print();
  void movePlayer(char input, Player &player);
  char getTile(int x, int y);
  void setTile(int x, int y, char tile);
  void processPlayerMove(Player& player, int targetx, int targety);
  void printDist(Player &player);
  void printSinDist(Player &player);
  void printFOV(Player &player);
  void clear();
  Pos getFOV(Player &player);
  std::vector<Pos> getNormalLine(Player &player, double degree, std::vector<char> stop);

private:
  std::vector < std::vector<char> > _map;
  int _maxDist;
};
