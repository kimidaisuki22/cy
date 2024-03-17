#pragma once
#include <cy/experiment/coroutine/coroutine_scheduler.h>
#include <cy/experiment/coroutine/switch_scheduler.h>
#include <cy/iteration/round_robin.h>
#include <vector>

namespace cy::experiment::coroutine {

class Scheduler_pack {
public:
  using Scheduler = Coroutine_scheduler;

  Scheduler_pack(size_t io_count, size_t compute_count);
  auto await_main() { return switch_to_scheduler(main_thread_); }
  auto await_io() {
    return switch_to_scheduler(*io_threads_[io_balance_.next()]);
  }
  auto await_compute() {
    return switch_to_scheduler(*compute_threads_[compute_balance_.next()]);
  }

  Scheduler main_thread_{};
  std::vector<std::unique_ptr<Scheduler>> io_threads_{};
  std::vector<std::unique_ptr<Scheduler>> compute_threads_{};

  iteration::Round_robin io_balance_;
  iteration::Round_robin compute_balance_;
};
} // namespace cy::experiment::coroutine
