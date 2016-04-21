#include "headers/ErrorLog.h"


std::vector<std::string> msgs;

void ErrorLog::print(std::string msg){
  int maxX, maxY;
  getmaxyx(stdscr, maxY, maxX);

  std::string fill = "";
  for(int i = 0; i < maxX; i++)
    fill += " ";

  mvprintw(maxY-1, 0, "%s", fill.c_str());

  mvprintw(maxY-1, 0, "%s", msg.c_str());

  // if(msgs.size() == 0)
  //    msgs.push_back(msg);
  //
  // else{
  //     bool f = false;
  //     for(int i = 0; i < msgs.size(); i++){
  //       if(msgs[i] == msg)
  //         f = true;
  //     }
  //     if(!f)
        //msgs.push_back(msg);

  //}
  // if(msgs[msgs.size()-1].compare(msg) != 0 )
  //   msgs.push_back(msg);
}

void ErrorLog::print_old(){
  for(int i = 0; i < msgs.size(); i++)
    std::cout << msgs[i] << std::endl;
}

int ErrorLog::msgHeight = 2;
//std::vector<std::string> ErrorLog::msgs = MakeVector();
