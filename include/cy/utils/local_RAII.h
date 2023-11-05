#pragma once
#include <algorithm>
namespace cy::utils {
template <typename Callable>
  requires requires(Callable obj) { obj(); }
class Local_RAII {
public:
  Local_RAII(Callable call) : final_call_(std::move(call)) {}
  Local_RAII(Local_RAII &&) = delete;
  Local_RAII(const Local_RAII &) = delete;

  ~Local_RAII() { final_call_(); }

private:
  Callable final_call_;
};
} // namespace cy::utils