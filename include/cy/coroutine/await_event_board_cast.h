#pragma once
#include <coroutine>
#include <mutex>
#include <vector>

namespace cy::coroutine {
template <typename T> class Awaitable_event_board_cast {
public:
  // return received count
  int send_event(T value) {
    std::unique_lock lock{mutex_};
    if (waitings_.empty()) {
      return 0;
    }
    for (auto &w : waitings_) {
      *w.output_dest = std::move(value);
      w.handle_.resume();
    }
    auto s = waitings_.size();
    waitings_.clear();
    return s;
  }
  bool has_waiting_task() {
    std::unique_lock lock{mutex_};
    return !waitings_.empty();
  }
  auto await() {
    struct awaitable {
      Awaitable_event_board_cast *queue_;
      // You don't need ptr here.
      T value_{};
      bool await_ready() { return false; }
      void await_suspend(std::coroutine_handle<> h) {
        queue_->waitings_.push_back({h, &this->value_});
      }
      T await_resume() { return std::move(value_); }
    };
    return awaitable{this};
  }

private:
  struct Waiting_handle {
    std::coroutine_handle<> handle_;
    T *output_dest{};
  };
  void add_waiting_task(Waiting_handle handle) {
    std::unique_lock lock{mutex_};
    waitings_.push_back(handle);
  }
  std::vector<Waiting_handle> waitings_{};
  std::mutex mutex_{};
};
} // namespace cy::coroutine
