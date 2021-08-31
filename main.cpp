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
  GameState endState = game.playGame();

  const unsigned int tipsLength = 3;
  const char *tips[tipsLength] = {
    "Collect '2' to reset your defence!",
    "Zombies are brainless, they'll follow you anywhere. Once you're out of view they move randomly.",
    "Find the finish line marker '<***>' to end the game."
  };

  endwin();
  switch(endState) {
    case WIN:
      cout << "You Win!!" << endl;
      break;
    case STOPPED:
      cout << "You quit, come back soon!" << endl;
      break;
    case DIED:
      cout << ":( You died, try again!" << endl;
      break;
  }
  cout << "===============================================" << endl;
  cout << "Here's a free tip: " << tips[rand() % tipsLength] << "" << endl;
  cout << "===============================================" << endl;
  return 0;
}
