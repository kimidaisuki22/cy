#pragma once
#include <deque>
#include <mutex>
#include <coroutine>
namespace cy::experiment::coroutine {
template <typename T> class Awaitable_input_queue {
public:
  void push(T value) {
    std::unique_lock lock{mutex_};
    if (waitings_.empty()) {
      values_.push_back(std::move(value));
    } else {
      auto h = waitings_.front();
      waitings_.pop_front();
      *h.output_dest = std::move(value);
      lock.unlock();
      h.handle_.resume();
    }
  }
  bool has_waiting_task() {
    std::unique_lock lock{mutex_};
    return !waitings_.empty();
  }
  auto await() {
    struct awaitable {
      Awaitable_input_queue *queue_;
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
    bool consumed{};
    {
      std::unique_lock lock{mutex_};
      if (!values_.empty()) {
        *handle.output_dest = values_.front();
        values_.pop_front();
        consumed = true;
      } else {
        waitings_.push_back(handle);
      }
    }
    if (consumed) {
      handle.handle_.resume();
    }
  }
  std::deque<Waiting_handle> waitings_{};
  std::deque<T> values_{};
  std::mutex mutex_{};
};
} // namespace cy::experiment::coroutine
