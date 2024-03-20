#pragma once
#include <cassert>
#include <coroutine>
#include <exception>
#include <optional>
#include <type_traits>
#include <utility>
namespace cy::coroutine {
template <typename T> class Simple_generator {
public:
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;

  struct promise_type {
    std::optional<std::remove_cvref_t<T>> current_value;
    std::exception_ptr exception_;
    std::suspend_always yield_value(T value) {
      current_value = value;
      return {};
    }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    Simple_generator get_return_object() {
      return Simple_generator{handle_type::from_promise(*this)};
    }
    void return_void() {}
    void unhandled_exception() { exception_ = std::current_exception(); }
  };

  Simple_generator(handle_type h) : coro(h) {}
  Simple_generator(const Simple_generator &) = delete;
  Simple_generator &operator=(const Simple_generator &) = delete;
  Simple_generator(Simple_generator &&o) noexcept
      : coro(std::exchange(o.coro, {})) {}
  ~Simple_generator() {
    if (coro)
      coro.destroy();
  }

  T getValue() { return *coro.promise().current_value; }

  bool next() {
    coro.resume();
    return !coro.done();
  }
  auto begin() {
    struct It {
      handle_type coco;
      It &operator++() {
        coco.resume();
        while (!coco.done() && !ref_value().has_value()) {
          coco.resume();
        }
        return *this;
      }
      bool operator!=(int) { return !coco.done(); }
      std::optional<std::remove_cvref_t<T>> &ref_value() {
        return coco.promise().current_value;
      }
      T operator*() {
        assert(ref_value().has_value());
        return *ref_value();
      }
    };
    return It{coro};
  }

  int end() { return 0; }

private:
  handle_type coro;
};

} // namespace cy::coroutine
