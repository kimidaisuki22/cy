#pragma once
#include <coroutine>
#include <exception>
#include <iostream>
#include <optional>
#include <utility>

namespace cy::experiment::coroutine {
template <typename T> class Simple_task;
template <typename T> class Simple_task_to_await {
public:
  Simple_task_to_await(Simple_task<T> &task) : task_(task) {}
  constexpr bool await_ready() const noexcept { return false; }

  constexpr void await_suspend(std::coroutine_handle<>) noexcept {
    task_.execute_to_done();
  }
  constexpr T await_resume() noexcept {
    return std::move(task_.getValue().value());
  }

private:
  Simple_task<T> &task_;
};
template <typename T> class Simple_task {
public:
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;

  struct promise_type {
    std::optional<T> current_value;
    std::exception_ptr exception_;

    std::suspend_never initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    Simple_task get_return_object() {
      return Simple_task{handle_type::from_promise(*this)};
    }
    void return_value(T value) { current_value = value; }
    void unhandled_exception() { exception_ = std::current_exception(); }
  };

  Simple_task(handle_type h) : coro(h) {}
  Simple_task(const Simple_task &) = delete;
  Simple_task &operator=(const Simple_task &) = delete;
  Simple_task(Simple_task &&o) noexcept : coro(std::exchange(o.coro, {})) {}
  ~Simple_task() {
    if (coro)
      coro.destroy();
  }

  std::optional<T> &getValue() { return coro.promise().current_value; }
  const std::optional<T> &getValue() const {
    return coro.promise().current_value;
  }
  bool done() const { return coro.done(); }
  void resume() { coro(); }
  void execute_to_done() {
    while (!done()) {
      std::cout << id << " Running\n";
      resume();
    }
  }
  Simple_task_to_await<T> operator co_await() { return *this; }

private:
  handle_type coro;
  static inline int id_src{};
  int id = {id_src++};
};

} // namespace cy::experiment::coroutine
