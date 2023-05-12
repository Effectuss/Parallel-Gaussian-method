#include "timer.h"

void Timer::DisplayTimerValues() {
  if (active_timer_) {
    std::chrono::duration<double> current_time =
        std::chrono::steady_clock::now() - start_time_;
    std::cout << current_time.count() << std::endl;
  } else {
    duration_ = end_time_ - start_time_;
    std::cout << duration_.count() << std::endl;
  }
}

void Timer::EndTimer() {
  end_time_ = std::chrono::steady_clock::now();
  duration_ = end_time_ - start_time_;
  active_timer_ = false;
}

void Timer::StartTimer() {
  active_timer_ = true;
  start_time_ = std::chrono::steady_clock::now();
}
