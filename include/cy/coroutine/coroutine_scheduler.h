#pragma once
#include <condition_variable>
#include <coroutine>
#include <deque>
namespace cy::coroutine {
class Coroutine_scheduler {
public:
  using Handle = std::coroutine_handle<>;
  void add(Handle handle);
  bool empty() const;
  Handle pop();
  void notify();
  // if predict return true, it stops waiting.
  void wait(auto stop_predict) {
    std::unique_lock lock{mutex_};
    wait_wake_up_.wait(lock, [&stop_predict, this] {
      return stop_predict() || !handles_.empty();
    });
  }

private:
  std::deque<Handle> handles_{};
  mutable std::mutex mutex_{};
  std::condition_variable wait_wake_up_{};
};
} // namespace cy::coroutine
