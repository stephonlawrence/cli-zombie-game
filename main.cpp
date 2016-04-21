#include <iostream>
#include <curses.h>
#include <stdio.h>
#include <string>

#include "headers/Level.h"
#include "headers/ErrorLog.h"
#include "headers/GameSystem.h"
//g++ -o main.o main.cpp -lncurses
using namespace std;


int main(){
  initscr();

  noecho();
  //nocbreak();
  timeout(0);

  GameSystem game("./data/level2.txt");
  game.playGame();

  endwin();
  //ErrorLog::print_old();
  return 0;
}
