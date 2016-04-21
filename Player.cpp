#include "headers/Player.h"

Player::Player(double fovRadius){
  _fovRadius = fovRadius;
  _defence = 2;
  _health = 10000;
  _damage = 5;
}
Player::Player(){
  _fovRadius = 5;
  _defence = 2;
  _health = 10000;
  _damage = 5;
}

void Player::attackPlayer(Player &player){
  player.doDamage(_damage);
}

void Player::getPosition(int &x, int &y){
  x = _x;
  y = _y;
}
void Player::setPosition(int x, int y){
  _x = x;
  _y = y;
}

void Player::doDamage(double dmg){
  _health = _health - (dmg - _defence);
  _defence = _defence - (_defence/10);
}

double Player::getHealth(){return _health;}

void Player::setHealth(double amount){_health = amount;}

double Player::getDamage(){return _damage;}

void Player::setDamage(double dmg){_damage = dmg;}

void Player::setDefence(double defence){_defence = defence;}

char Player::getRef(){return _ref;}

void Player::setRef(char ref){_ref = ref;}

std::vector < std::vector<Pos> > Player::getFov(){
  return _fov;
}

double Player::getFovRadius(){ return _fovRadius;}
