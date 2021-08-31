#include <iostream>
#include <curses.h>
#include <stdio.h>
#include <string>
#include <filesystem>
#include <vector>

#include "headers/Level.h"
#include "headers/ErrorLog.h"
#include "headers/GameSystem.h"
//g++ -o main.o main.cpp -lncurses
using namespace std;
namespace fs = filesystem;

int main(){

  cout << "Choose a level from the list by typing a number then pressing enter: " << endl;

  string path = "./data";
  unsigned int choiceCounter = 1;
  vector<string> levels;
  for (fs::directory_entry const& entry : fs::directory_iterator(path)) {
    levels.push_back(entry.path());
  }
  for (string entry : levels) {
    cout << "[" << choiceCounter << "] " << entry << endl;
    choiceCounter++;
  }
  unsigned int choice = 0;
  do {
    choice = 1;
    cin >> choice;
    if (choice < 1 || choice > levels.size())
      cout << "That is not an option choose a different one.";
  }
  while (choice < 1 || choice > levels.size());

  auto chosenLevel = levels.at(choice - 1);

  initscr();

  noecho();
  //nocbreak();
  timeout(0);

  GameSystem game(chosenLevel);
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
