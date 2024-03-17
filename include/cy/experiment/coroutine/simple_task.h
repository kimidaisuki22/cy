#pragma once
#include <coroutine>
#include <exception>
#include <utility>

namespace cy::experiment::coroutine {

template <typename T> class Simple_task {
public:
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;

  struct promise_type {
    std::exception_ptr exception_;
    T result_value_;
    std::coroutine_handle<> pending_coroutine_{};

    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept {
      if (pending_coroutine_) {
        pending_coroutine_.resume();
      }
      return {};
    }
    Simple_task get_return_object() {
      return Simple_task{handle_type::from_promise(*this)};
    }
    // return value is called before the final suspend.
    void return_value(T returned_value) {
      result_value_ = std::move(returned_value);
    }
    void unhandled_exception() { exception_ = std::current_exception(); }
  };

  Simple_task(handle_type h) : coro(h) {}
  Simple_task(const Simple_task &) = delete;
  Simple_task &operator=(const Simple_task &) = delete;
  Simple_task(Simple_task &&o) noexcept : coro(std::exchange(o.coro, {})) {}
  ~Simple_task() {}

  auto operator co_await() {
    struct awaitable {
      Simple_task *self_;
      T *result_value_{};
      bool await_ready() { return false; }
      void await_suspend(std::coroutine_handle<> h) {
        self_->coro.promise().pending_coroutine_ = h;
      }
      T await_resume() { return std::move(*result_value_); }
    };
    return awaitable{this, &coro.promise().result_value_};
  }

private:
  handle_type coro;
};
} // namespace cy::experiment::coroutine
