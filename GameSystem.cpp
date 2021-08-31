#include "headers/GameSystem.h"
#include <sstream>
#include <iomanip>

GameSystem::GameSystem(std::string filename){
  _level.load(filename, _player, _enemies);
  std::srand(std::time(NULL));
  _state = PLAYING;

}

GameState GameSystem::playGame(){
  _etimer.reset();
  _gtimer.reset();
  while(_state == PLAYING){
    if (_player.getHealth() <= 0) {
      _state = DIED;
      break;
    }
    if(_gtimer.elapsed() > 0.0001){
      processInput();
      _gtimer.reset();
    }
  }
  return _state;
}

void GameSystem::processInput(){
  char input;

  _level.clear();
  _level.printFOV(_player);
  //_level.print();

  std::ostringstream sshealth;
  sshealth << std::fixed << std::setprecision(2) << _player.getHealth();
  std::string health_indicator = sshealth.str() + "%";

  std::ostringstream ssdefence;
  ssdefence << std::fixed << std:: setprecision(2) << _player.getDefence();
  std:: string defence_indicator = ssdefence.str();

  ErrorLog::print("Press w, a, s, d to move | [HEALTH - "+ health_indicator +" | "+ defence_indicator +"]");

  input = getch();

  if(input == 'q')
    _state = STOPPED;
  else{
    _state = _level.movePlayer(input, _player);
    processEnemyMove();
  }
}

void GameSystem::processEnemyMove(){


  if(_etimer.elapsed() >= 0.25){
    //ErrorLog::print("size: "+std::to_string(_enemies.size()) );
    for(int i = 0; i < _enemies.size(); i++){
        Pos pos = _level.getFOV(_enemies[i]);
        if(pos.c == ' '){
          int n = rand() % 5 + 1;
          char c;
          switch(n){
            case 1:
              c = 'w';
              break;
            case 2:
              c = 'a';
              break;
            case 3:
              c = 's';
              break;
            case 4:
              c = 'd';
              break;
            case 5:
              c = 'n';
              break;
          }
          _level.movePlayer(c, _enemies[i]);
        }
        else if(pos.c == '@'){
          int x, y;
          std::vector<char> stoppers;
          stoppers.push_back('#');
          stoppers.push_back('@');
          stoppers.push_back('Z');
          _enemies[i].getPosition(x, y);
          if(std::abs(x - pos.x) <= 1 && std::abs(y - pos.y) <= 1)
            _enemies[i].attackPlayer(_player);
            
          // algorithm for finding player for each enemy
          if(std::abs(x - pos.x) >= std::abs(y - pos.y)){
            std::vector <Pos> d = _level.getNormalLine(_enemies[i], 0, stoppers),
                              a = _level.getNormalLine(_enemies[i], 180, stoppers);
            if(x < pos.x && d.size() > 0 && d[d.size() - 1].c != '#' && d[d.size() - 1].c != 'Z'){
              _level.movePlayer('d', _enemies[i]);
            }else if(x > pos.x && a.size() > 0 && a[a.size() - 1].c != '#' && a[a.size() - 1].c != 'Z'){
              _level.movePlayer('a', _enemies[i]);
            }
          }else if(std::abs(y - pos.y) > std::abs(x - pos.x)){
            std::vector <Pos> s = _level.getNormalLine(_enemies[i], 90, stoppers),
                              w = _level.getNormalLine(_enemies[i], 270, stoppers);
            if(y < pos.y && s.size() > 0 && s[s.size() - 1].c != '#' && s[s.size() - 1].c != 'Z'){
              _level.movePlayer('s', _enemies[i]);
            }else if(y > pos.y && w.size() > 0 && w[w.size() - 1].c != '#' && w[w.size() - 1].c != 'Z'){
              _level.movePlayer('w', _enemies[i]);
            }
          }
        }

    }
    _etimer.reset();
  }
}
