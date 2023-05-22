#ifndef _UTILS_BARRIER_H_
#define _UTILS_BARRIER_H_

#include <condition_variable>
#include <mutex>
#include <stdexcept>
#include <thread>

class Barrier {
 public:
  explicit Barrier(std::size_t num)
      : num_threads_(num), wait_count_(0), instance_(0), mutex_(), cv_() {
    if (num == 0) {
      throw std::invalid_argument("Barrier thread count cannot be 0");
    }
  }

  ~Barrier() = default;
  Barrier(const Barrier&) = delete;
  Barrier(Barrier&&) = delete;
  void operator=(const Barrier&) = delete;
  void operator=(Barrier&&) = delete;

  void Wait();

 private:
  std::size_t num_threads_;     // number of threads using barrier
  std::size_t wait_count_;      // counter to keep track of waiting threads
  std::size_t instance_;        // counter to keep track of barrier use count
  std::mutex mutex_;            // mutex used to protect resources
  std::condition_variable cv_;  // condition variable used to block threads
};

#endif  // _UTILS_BARRIER_H_