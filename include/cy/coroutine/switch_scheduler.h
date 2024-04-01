#pragma once
#include <cy/coroutine/coroutine_scheduler.h>
namespace cy::coroutine {
inline auto switch_to_scheduler(Coroutine_scheduler &scheduler) {
  struct awaitable {
    Coroutine_scheduler *scheduler_ptr_;
    bool await_ready() { return false; }
    void await_suspend(std::coroutine_handle<> h) { scheduler_ptr_->add(h); }
    Coroutine_scheduler &await_resume() { return *scheduler_ptr_; }
  };
  return awaitable{&scheduler};
}
} // namespace cy::coroutine