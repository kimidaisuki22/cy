#pragma once
#include <cy/experiment/coroutine/coroutine_scheduler.h>
#include <cy/experiment/coroutine/scheduler_pack.h>
namespace cy::experiment::coroutine {
inline bool is_no_task(Coroutine_scheduler &scheduler) {
  return scheduler.empty();
}
inline bool is_no_task(Scheduler_pack &scheduler) {
  if (!is_no_task(scheduler.main_thread_)) {
    return false;
  }
  for (auto &s : scheduler.io_threads_) {
    if (!is_no_task(*s)) {
      return false;
    }
  }
  for (auto &s : scheduler.compute_threads_) {
    if (!is_no_task(*s)) {
      return false;
    }
  }
  return true;
}
} // namespace cy::experiment::coroutine