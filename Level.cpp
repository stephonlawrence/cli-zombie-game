#include "headers/Level.h"
#include "headers/GameState.h"

const double PI = 3.14159265;
void Level::load(std::string filename, Player &player, std::vector<Player> &enemies){
  _maxDist = 5;
  std::ifstream file(filename);
  if(!file.is_open()){
    ErrorLog::print("file could not be opened.");
    return;
  }

  int y =0, x=0;
  char c;

  _map.push_back(std::vector< char >());

  while(!file.eof()){
    c = file.get();
    if(c == '\n'){
      y++;
      _map.push_back( std::vector< char >() );
      x=0;
      continue;
    }
    switch(c){
      case '@':
        player.setPosition(x, y);
        player.setRef('@');
        break;
      case 'Z':
        Player p(10);
        p.setPosition(x, y);
        p.setRef('Z');
        enemies.push_back(p);
        break;
    }
    //if(c == '@' || c == 'Z' || c == '2' || c == '#' || c == ' '){
      _map[y].push_back(c);
    // }else{
    //   _map[y].push_back(' ');
    // }
    x++;
  }
  file.close();
}

char Level::getTile(int x, int y){
  return _map[y][x];
}

void Level::setTile(int x, int y, char tile){
  _map[y][x] = tile;
}

GameState Level::processPlayerMove(Player& player, int targetx, int targety){

  int playerx, playery;
  player.getPosition(playerx, playery);

  switch(getTile(targetx, targety)){
    case ' ':
      setTile(playerx, playery, ' ');
      setTile(targetx, targety, player.getRef());
      player.setPosition(targetx, targety);
      break;
    case '2':
      if (player.getRef() == '@') {
        player.setDefence(2);
        setTile(playerx, playery, ' ');
        setTile(targetx, targety, player.getRef());
        player.setPosition(targetx, targety);
      }
      break;
    case '<':
    case '*':
    case '>':
      if (player.getRef() == '@') {
        setTile(playerx, playery, ' ');
        setTile(targetx, targety, player.getRef());
        player.setPosition(targetx, targety);
        return WIN;
      }
      break;
    case '@':
      if(player.getRef() == 'Z'){
        // process damage
      }
      break;
    //case 'Z':

  }
  return PLAYING;
}

GameState Level::movePlayer(char input, Player &player){

  int playerx, playery;
  player.getPosition(playerx, playery);
  switch(input){
    case 'w':
    case 'W':
      return processPlayerMove(player, playerx, playery - 1);
      break;
    case 'a':
    case 'A':
      return processPlayerMove(player, playerx - 1, playery);
      break;
    case 's':
    case 'S':
      return processPlayerMove(player, playerx, playery + 1);
      break;
    case 'd':
    case 'D':
      return processPlayerMove(player, playerx + 1, playery);
      break;
    default:
      ;
      // std::string val = "Invalid input: "+std::to_string(input)+" ... Press any key to continue.";
      // ErrorLog::print(val.c_str());
      // getch();
  return PLAYING;
  }
}

void Level::print(){
  int y = 0, x = 0;
  for(y = 0; y < _map.size(); y++){
    for(x = 0; x < _map[y].size(); x++){
      mvaddch(y,x,_map[y][x]);
    }
  }
}


std::vector<Pos> Level::getNormalLine(Player &player, double degree, std::vector<char> stop){
    std::vector<Pos> line;
    int h, k;
    player.getPosition(h, k);
    int count = 0;
    double r = 0;
    for(r = 0, count = 0; r <= player.getFovRadius(); r++, count++){
      line.push_back(Pos());
      int x = std::round(h + (r * std::cos(degree)));
      int y = std::round(k + (r * std::sin(degree)));

      if(y < _map.size() && x < _map[y].size() && y >= 0 && x >= 0){
        line[count].c = _map[y][x];
        bool found = false;
        for(int i = 0; i < stop.size(); i++){
          if(_map[y][x] == stop[i]){
            found = true;
            break;
          }
        }
        if(!found)
          break;
      }
    }
    return line;
}

// 360 degrees vector then normal line vector of positions
// [ [{x, y}, {x, y}, {x, y}] ]
Pos Level::getFOV(Player &player){
  int h, k;
  player.getPosition(h, k);
  std::vector < std::vector<Pos> > data = player.getFov();
  Pos p;
  p.x = 0;
  p.y = 0;
  p.c = ' ';
  // r^2 = (x - h)^2 + (y - k)^2
  // x = h + (r * cos(t))
  // y = k + (r * sin(t))
  double t = 0;
  double interval = 1;
  double r = 0;
  //double r = 10;
  data.clear();
  int dc = 0;
  int rc = 0;
  double n;
  for(n = 0, dc = 0; n < 360; n+= interval, dc++){
    if(data.size() < n + 1)
      data.push_back(std::vector<Pos>());
    double degree = (n * PI) / 180;

    for(r = 0, rc = 0; r <= player.getFovRadius(); r+=1, rc++){
      if(data[dc].size() < r + 1)
        data[dc].push_back(Pos());
      int x = data[dc][rc].x = std::round(h + (r * std::cos(degree)));
      int y = data[dc][rc].y = std::round(k + (r * std::sin(degree)));

      if(y < _map.size() && x < _map[y].size() && y >= 0 && x >= 0){
        data[dc][rc].c = _map[y][x];
        if(_map[y][x] == '@'){
          p.x = x;
          p.y = y;
          p.c = '@';
        }
        if(_map[y][x] == '#')
          break;
      }

    }
  }
  return p;
}

void Level::printFOV(Player &player){
  int playerx, playery;
  player.getPosition(playerx, playery);

  // r^2 = (x - h)^2 + (y - k)^2
  // x = h + (r * cos(t))
  // y = k + (r * sin(t))
  double t = 0;
  double interval = 1;
  double r = 0;
  //double r = 10;
  for(double n = 0; n < 360; n+= interval){

    double degree = (n * PI) / 180;

    double h = playerx;
    double k = playery;
    for(r = 0; r <= player.getFovRadius(); r+=1){
      double x = h + (r * std::cos(degree));
      double y = k + (r * std::sin(degree));

      x = std::round(x);
      y = std::round(y);
      if(y < _map.size() && x < _map[y].size() && y >= 0 && x >= 0){
        mvaddch(y, x, _map[y][x]);
        if(_map[y][x] == ' ')
          mvaddch(y, x, '.');
        if(_map[y][x] == '#')
          break;
      }

    }
  }
}

void Level::printSinDist(Player &player){
  int playerx, playery;
  player.getPosition(playerx, playery);

  // r^2 = (x - h)^2 + (y - k)^2
  // x = h + (r * cos(t))
  // y = k + (r * sin(t))
  double t = 0;
  double interval = 1;
  double r = _maxDist;
  //double r = 10;
  for(double n = 0; n < 360; n+= interval){

    double degree = (n * PI) / 180;

    double h = playerx;
    double k = playery;

    double x = h + (r * std::cos(degree));
    double y = k + (r * std::sin(degree));
    //double less = (h < x)? h : x, more = (h < x)? x : h;
    double change = 1;
    double max = std::abs(x - h) / change;

    for (double i = h, g = 0; g < max; g+= change, i += (x - h == 0) ? 0 : ((x - h) / std::abs(x - h)) * change){
      // y = mx + b
      // b = y - mx

      double j;
      // if(x - h == 0)
      //   j = h;
      // else{
        //double m = (y - k) / (x - h);
        double m = (2*y) / ((2*x) - (2*h) - (2*k) - (2*r));
        double b = y - m * x;
        j = m * i + b;
      //}
      int vx = std::floor(i), vy = std::floor(j);
      if(vy < _map.size() && vx < _map[vy].size() && vy >= 0 && vx >= 0){

        mvaddch(vy, vx, _map[vy][vx]);
        if(_map[vy][vx] == ' ')
           mvaddch(vy, vx, '.');
      }

    }
  }
}

void Level::printDist(Player &player){

  int playerx, playery;
  player.getPosition(playerx, playery);


  // domain
  int minx = (playerx - _maxDist < 0) ? 0 : playerx - _maxDist;
  int miny = (playery - _maxDist < 0) ? 0 : playery - _maxDist;

  // range
  int maxx = playerx + _maxDist;
  int maxy = playery + _maxDist;
  int y, x;
  for(y = miny; y < _map.size() && y <= maxy; y++){
    for(x = minx; x < _map[y].size() && x <= maxx; x++){
      mvaddch(y, x, _map[y][x]);
    }
  }

}

void Level::clear(){
  int y = 0, x = 0;
  for(y = 0; y < _map.size(); y++){
    for(x = 0; x < _map[y].size(); x++){
      mvaddch(y,x,' ');
    }
  }
}
