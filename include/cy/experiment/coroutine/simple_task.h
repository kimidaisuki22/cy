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

    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    Simple_task get_return_object() { return Simple_task{handle_type::from_promise(*this)}; }
    void return_value(T returned_value) {}
    void unhandled_exception() { exception_ = std::current_exception(); }
  };

  Simple_task(handle_type h) : coro(h) {}
  Simple_task(const Simple_task &) = delete;
  Simple_task &operator=(const Simple_task &) = delete;
  Simple_task(Simple_task &&o) noexcept : coro(std::exchange(o.coro, {})) {}
  ~Simple_task() {}

private:
  handle_type coro;
};
} // namespace cy::experiment::coroutine
