#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

class Barrier {
 public:
  Barrier(unsigned int n) : thread_count_(n) {
    threads_waiting_ = 0;
    is_not_waiting_ = false;
  }
  Barrier(const Barrier &) = delete;
  void Wait() {
    if (threads_waiting_.fetch_add(1) >= thread_count_ - 1) {
      is_not_waiting_ = true;
      wait_variable_.notify_all();
      threads_waiting_.store(0);
    } else {
      std::unique_lock<std::mutex> lock(mutex_);
      wait_variable_.wait(lock, [&] { return is_not_waiting_; });
    }
  }

 private:
  const unsigned int thread_count_;
  std::atomic<unsigned int> threads_waiting_;
  bool is_not_waiting_;
  std::condition_variable wait_variable_;
  std::mutex mutex_;
}; 