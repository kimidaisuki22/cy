#pragma once
#include <cy/coroutine/coroutine_scheduler.h>
#include <cy/coroutine/switch_scheduler.h>
#include <cy/iteration/round_robin.h>
#include <vector>

namespace cy::coroutine {

class Scheduler_pack {
public:
  using Scheduler = Coroutine_scheduler;

  Scheduler_pack(size_t io_count, size_t compute_count);
  auto await_main() { return switch_to_scheduler(main_thread_); }
  auto await_io() {
    size_t index;
    {
      std::unique_lock lock{io_index_mutex_};
      index = io_balance_.next();
    }
    return switch_to_scheduler(*io_threads_[index]);
  }
  auto await_compute() {
    size_t index;
    {
      std::unique_lock lock{compute_index_mutex_};
      index = compute_balance_.next();
    }
    return switch_to_scheduler(*compute_threads_[index]);
  }

  Scheduler main_thread_{};
  std::vector<std::unique_ptr<Scheduler>> io_threads_{};
  std::vector<std::unique_ptr<Scheduler>> compute_threads_{};

  iteration::Round_robin io_balance_;
  std::mutex io_index_mutex_;
  iteration::Round_robin compute_balance_;
  std::mutex compute_index_mutex_;
};
} // namespace cy::coroutine
