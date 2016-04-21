#include "headers/Timer.h"


void Timer::reset() { beg_ = clock_::now(); }
double Timer::elapsed() const {
  return std::chrono::duration_cast<second_> (clock_::now() - beg_).count();
}
