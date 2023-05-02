#ifndef _UTILS_TIMER_H_
#define _UTILS_TIMER_H_

#include <chrono>
#include <iostream>

class Timer {
 public:
  void StartTimer() {
    active_timer_ = true;
    start_time_ = std::chrono::steady_clock::now();
  }

  void EndTimer() {
    end_time_ = std::chrono::steady_clock::now();
    duration_ = end_time_ - start_time_;
    active_timer_ = false;
  }

void DisplayTimerValues() {
  if(active_timer_) {
        auto current_time = std::chrono::steady_clock::now() - start_time_;
        std::cout << current_time.count() << std::endl;
  } else {
        duration_ = end_time_ - start_time_;
        std::cout << duration_.count() << std::endl;
  }
    }

 private:
    bool active_timer_{false};
    std::chrono::time_point<std::chrono::steady_clock> start_time_, end_time_;
    std::chrono::duration<double> duration_;
};

#endif // _UTILS_TIMER_H_