#ifndef _UTILS_BARRIER_H_
#define _UTILS_BARRIER_H_

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

class Barrier {
 public:
  explicit Barrier(int i_count) : threshold_(i_count), count_(i_count) {}
  ~Barrier() = default;
  Barrier(const Barrier&) = delete;
  Barrier(Barrier&&) = delete;
  void operator=(const Barrier&) = delete;
  void operator=(Barrier&&) = delete;

  void Wait();

 private:
  std::mutex mtx_;
  std::condition_variable cond_;
  int generation_ = 0;
  int threshold_;
  int count_;
};
#endif  // _UTILS_BARRIER_H_