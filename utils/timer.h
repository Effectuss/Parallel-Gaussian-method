#ifndef _UTILS_TIMER_H_
#define _UTILS_TIMER_H_

#include <chrono>
#include <iostream>

class Timer {
 public:
  void StartTimer();
  void EndTimer();
  void DisplayTimerValues();

 private:
  bool active_timer_{false};
  std::chrono::time_point<std::chrono::steady_clock> start_time_, end_time_;
  std::chrono::duration<double> duration_;
};

#endif  // _UTILS_TIMER_H_