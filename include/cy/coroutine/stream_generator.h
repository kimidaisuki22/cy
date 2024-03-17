#pragma once

#pragma once
#include <cassert>
#include <coroutine>
#include <exception>
#include <optional>
#include <type_traits>
#include <utility>
namespace cy::coroutine {
template <typename Output, typename Input> class Stream_generator {
public:
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;

  struct promise_type {
    std::optional<std::remove_cvref_t<Output>> current_value;
    Input intput_value_{};

    std::exception_ptr exception_;
    auto yield_value(Output value) {
      current_value = value;
      struct Awaitable {
        promise_type *self_;
        bool await_ready() { return false; }
        void await_suspend(std::coroutine_handle<> h) {}
        Input &await_resume() { return self_->intput_value_; }
      };
      current_value = value;
      return Awaitable{this};
    }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    Stream_generator get_return_object() {
      return Stream_generator{handle_type::from_promise(*this)};
    }
    void return_void() {}
    void unhandled_exception() { exception_ = std::current_exception(); }
  };

  Stream_generator(handle_type h) : coro(h) {}
  Stream_generator(const Stream_generator &) = delete;
  Stream_generator &operator=(const Stream_generator &) = delete;
  Stream_generator(Stream_generator &&o) noexcept
      : coro(std::exchange(o.coro, {})) {}
  ~Stream_generator() {
    if (coro)
      coro.destroy();
  }

  Output getValue() { return *coro.promise().current_value; }
  Output operator()(Input input) {
    coro.promise().intput_value_ = input;
    coro.resume();
    return getValue();
  }

private:
  handle_type coro;
};

} // namespace cy::coroutine
