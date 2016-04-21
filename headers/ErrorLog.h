#pragma once

#include <curses.h>
#include <string>
#include <vector>
#include <iostream>

class ErrorLog{
public:
  static void print(std::string msg);
  static int msgHeight;

  static void print_old();
  //static std::vector< std::string > msgs;

};
