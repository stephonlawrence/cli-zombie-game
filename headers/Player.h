#pragma once

#include <vector>
#include "../Position.cpp"

class Player{
public:
  Player(double fovRadius);
  Player();

  void attackPlayer(Player &player);
  void getPosition(int &x, int &y);
  void setPosition(int x, int y);

  void doDamage(double dmg);

  double getHealth();
  void setHealth(double amount);

  double getDamage();
  void setDamage(double dmg);

  void setDefence(double defence);

  char getRef();
  void setRef(char ref);

  double getFovRadius();

  std::vector < std::vector<Pos> > getFov();

private:
  int _x;
  int _y;
  double _health;
  double _damage;
  double _defence;
  char _ref;
  std::vector < std::vector<Pos> > _fov;
  double _fovRadius;
};
