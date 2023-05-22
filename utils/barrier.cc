#include "barrier.h"

void Barrier::Wait() {
  std::unique_lock<std::mutex> lock(mutex_);  // acquire lock
  std::size_t inst = instance_;  // store current instance for comparison
                                 // in predicate

  if (++wait_count_ == num_threads_) {  // all threads reached barrier
    wait_count_ = 0;                    // reset wait_count
    instance_++;  // increment instance for next use of barrier and to
                  // pass condition variable predicate
    cv_.notify_all();
  } else {  // not all threads have reached barrier
    cv_.wait(lock, [this, &inst]() { return instance_ != inst; });
  }
}